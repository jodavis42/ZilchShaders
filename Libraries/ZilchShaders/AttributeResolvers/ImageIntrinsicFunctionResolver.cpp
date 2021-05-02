///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "ImageIntrinsicFunctionResolver.hpp"
#include "ZilchShaders/AttributeResolvers/AttributeParsingUtilities.hpp"

namespace Zero
{

//-------------------------------------------------------------------ImageIntrinsicFunctionAttribute
ZilchDefineType(ImageIntrinsicFunctionAttribute, builder, type)
{
  ZilchBindDefaultCopyDestructor();
  type->CreatableInScript = false;
}

//-------------------------------------------------------------------ImageIntrinsicFunctionResolver
void ImageIntrinsicFunctionResolver::Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute)
{
  Zilch::FunctionNode* fnNode = Zilch::Type::DynamicCast<Zilch::FunctionNode*>(node);
  if(fnNode == nullptr)
  {
    String msg = String::Format("Attribute [%s] is only valid on functions.", translator->mSettings->mNameSettings.mImageIntrinsicFunctionAttribute.c_str());
    translator->SendTranslationError(attribute.GetLocation(), msg);
    return;
  }

  // Validate and parse the attribute
  Zilch::HandleOf<ImageIntrinsicFunctionAttribute> intrinsicAttribute = ZilchAllocate(ImageIntrinsicFunctionAttribute);
  if(!intrinsicAttribute->Parse(translator, attribute))
    return;

  if(attributes.FindFirstAttribute(translator->mSettings->mNameSettings.mStaticAttribute) == nullptr)
  {
    translator->SendTranslationError(node->Location, String::Format("Attribute [%s] can only be used on a static function.", attribute.mAttributeName.c_str()));
    return;
  }

  if(fnNode->Parameters.Size() < 1)
  {
    translator->SendTranslationError(fnNode->Location, String::Format("Functions declared with %s must have at least one argument.", attribute.mAttributeName.c_str()));
    return;
  }

  // Register the callback for this function based upon the first arg type.
  MemberFunctionResolverIRFn resolverFn = nullptr;
  ZilchShaderIRType* shaderParam0Type = translator->FindType(fnNode->Parameters[0]);
  if(shaderParam0Type->mBaseType == ShaderIRTypeBaseType::Image)
    resolverFn = TranslateImageIntrinsic;
  else if(shaderParam0Type->mBaseType == ShaderIRTypeBaseType::SampledImage)
    resolverFn = TranslateSampledImageIntrinsic;
  else
  {
    translator->SendTranslationError(fnNode->Parameters[0]->Location, "Argument 1 must be either an Image or SampledImage type.");
    return;
  }

  ZilchShaderIRLibrary* library = translator->mLibrary;
  Zilch::Type* owningType = AttributeParsingUtilities::GetOwningType(translator, shaderType, attributes);
  
  TypeResolvers& resolvers = library->mTypeResolvers[owningType];
  resolvers.RegisterFunctionResolver(fnNode->DefinedFunction, resolverFn);
  // Attach the intrinsic attribute data to the function so we can look it up later
  fnNode->DefinedFunction->Add(*intrinsicAttribute);
  fnNode->DefinedFunction->AddAttribute(translator->mSettings->mNameSettings.mIntrinsicAttribute);
}

void ImageIntrinsicFunctionResolver::TranslateImageIntrinsic(ZilchSpirVFrontEnd* translator, Zilch::FunctionCallNode* functionCallNode, Zilch::MemberAccessNode* memberAccessNode, ZilchSpirVFrontEndContext* context)
{
  ImageIntrinsicFunctionAttribute* intrinsicAttribute = memberAccessNode->AccessedFunction->Has<ImageIntrinsicFunctionAttribute>();
  ReturnIf(intrinsicAttribute == nullptr, , "Failed to find the pre-parsed intrinsic information");

  ZilchShaderIRType* returnType = translator->mLibrary->FindType(functionCallNode->ResultType);
  Array<IZilchShaderIR*> arguments;
  translator->GetFunctionCallArguments(functionCallNode, (IZilchShaderIR*)nullptr, arguments, context);

  // When the first parameter is an image, simply output the arguments as we received them doing no special remapping
  ZilchShaderIROp* op = translator->BuildIROpNoBlockAdd(intrinsicAttribute->mOpType, returnType, context);
  WriteArguments(translator, *intrinsicAttribute, op, arguments, 0, context);
}

void ImageIntrinsicFunctionResolver::TranslateSampledImageIntrinsic(ZilchSpirVFrontEnd* translator, Zilch::FunctionCallNode* functionCallNode, Zilch::MemberAccessNode* memberAccessNode, ZilchSpirVFrontEndContext* context)
{
  ImageIntrinsicFunctionAttribute* intrinsicAttribute = memberAccessNode->AccessedFunction->Has<ImageIntrinsicFunctionAttribute>();
  ReturnIf(intrinsicAttribute == nullptr, , "Failed to find the pre-parsed intrinsic information");

  ZilchShaderIRType* returnType = translator->mLibrary->FindType(functionCallNode->ResultType);
  Array<IZilchShaderIR*> arguments;
  translator->GetFunctionCallArguments(functionCallNode, (IZilchShaderIR*)nullptr, arguments, context);

  // When the first parameter is a sampled image, we have to extract the image from the sampled image then append the rest of the arguments.
  ZilchShaderIROp* sampledImageOp = translator->GetOrGenerateValueTypeFromIR(arguments[0], context);
  ZilchShaderIRType* sampledImageType = sampledImageOp->mResultType->GetValueType();
  ZilchShaderIRType* imageType = sampledImageType->mParameters[0]->As<ZilchShaderIRType>();
  // Pull the image out of the sampled image.
  ZilchShaderIROp* imageOp = translator->BuildIROp(context->mCurrentBlock, OpType::OpImage, imageType, sampledImageOp, context);
  ZilchShaderIROp* op = translator->BuildIROpNoBlockAdd(intrinsicAttribute->mOpType, returnType, context);
  op->mArguments.PushBack(imageOp);
  // Append all of the arguments after the 1st one in the given signature
  WriteArguments(translator, *intrinsicAttribute, op, arguments, 1, context);
}

void ImageIntrinsicFunctionResolver::WriteArguments(ZilchSpirVFrontEnd* translator, ImageIntrinsicFunctionAttribute& intrinsicAttribute, ZilchShaderIROp* op, Array<IZilchShaderIR*>& arguments, size_t startIndex, ZilchSpirVFrontEndContext* context)
{
  // If there's no operands location, then just write the arguments as is.
  // It's only if there's a mask and location that we write this (since not all image ops have a mask).
  if(intrinsicAttribute.mOperandsLocation == -1)
  {
    for(size_t i = startIndex; i < arguments.Size(); ++i)
      op->mArguments.PushBack(translator->GetOrGenerateValueTypeFromIR(arguments[i], context));
  }
  // Otherwise, add all of the given arguments, but put the operands mask in-between based upon the specified location.
  // This location isn't consistent for all image functions so it became an exposed value.
  else
  {
    for(size_t i = startIndex; i < intrinsicAttribute.mOperandsLocation && i < arguments.Size(); ++i)
      op->mArguments.PushBack(translator->GetOrGenerateValueTypeFromIR(arguments[i], context));
    op->mArguments.PushBack(translator->GetOrCreateConstantIntegerLiteral(intrinsicAttribute.mOperands));
    for(size_t i = intrinsicAttribute.mOperandsLocation; i < arguments.Size(); ++i)
      op->mArguments.PushBack(translator->GetOrGenerateValueTypeFromIR(arguments[i], context));
  }
  context->mCurrentBlock->AddOp(op);
  context->PushIRStack(op);
}

}//namespace Zero
