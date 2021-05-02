#include "Precompiled.hpp"

#include "SampledImageIntrinsicFunctionResolver.hpp"
#include "ZilchShaders/AttributeResolvers/AttributeParsingUtilities.hpp"

namespace Zero
{

//-------------------------------------------------------------------SampledImageIntrinsicFunctionAttribute
ZilchDefineType(SampledImageIntrinsicFunctionAttribute, builder, type)
{
  ZilchBindDefaultCopyDestructor();
  type->CreatableInScript = false;
}

//-------------------------------------------------------------------SampledImageIntrinsicFunctionResolver
void SampledImageIntrinsicFunctionResolver::Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute)
{
  Zilch::FunctionNode* fnNode = Zilch::Type::DynamicCast<Zilch::FunctionNode*>(node);
  if(fnNode == nullptr)
  {
    String msg = String::Format("Attribute [%s] is only valid on functions.", translator->mSettings->mNameSettings.mImageIntrinsicFunctionAttribute.c_str());
    translator->SendTranslationError(attribute.GetLocation(), msg);
    return;
  }

  // Validate and parse the attribute
  Zilch::HandleOf<SampledImageIntrinsicFunctionAttribute> intrinsicAttribute = ZilchAllocate(SampledImageIntrinsicFunctionAttribute);
  if(!intrinsicAttribute->Parse(translator, attribute))
    return;

  if(attributes.FindFirstAttribute(translator->mSettings->mNameSettings.mStaticAttribute) == nullptr)
  {
    translator->SendTranslationError(node->Location, String::Format("Attribute [%s] can only be used on a static function.", attribute.mAttributeName.c_str()));
    return;
  }

  if(fnNode->Parameters.Size() < 1)
  {
    translator->SendTranslationError(fnNode->Location, "Must have at least one argument");
    return;
  }

  MemberFunctionResolverIRFn resolverFn = nullptr;
  ZilchShaderIRType* shaderParam0Type = translator->FindType(fnNode->Parameters[0]);
  // Validate that the starting signature is either: (SampledImage, ...) or (Image, Sampler, ...)
  if(shaderParam0Type->mBaseType == ShaderIRTypeBaseType::SampledImage)
    resolverFn = TranslateSampledImageIntrinsic;
  else if(shaderParam0Type->mBaseType == ShaderIRTypeBaseType::Image && fnNode->Parameters.Size() >= 2)
  {
    ZilchShaderIRType* shaderParam1Type = translator->FindType(fnNode->Parameters[1]);
    if(shaderParam1Type->mBaseType == ShaderIRTypeBaseType::Sampler)
      resolverFn = TranslateSplitSampledImageIntrinsic;
  }
  
  if(resolverFn == nullptr)
  {
    translator->SendTranslationError(fnNode->Parameters[0]->Location, "Expected signature of (SampledImage, ...) or (Image, Sampler, ...).");
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

void SampledImageIntrinsicFunctionResolver::TranslateSampledImageIntrinsic(ZilchSpirVFrontEnd* translator, Zilch::FunctionCallNode* functionCallNode, Zilch::MemberAccessNode* memberAccessNode, ZilchSpirVFrontEndContext* context)
{
  SampledImageIntrinsicFunctionAttribute* intrinsicAttribute = memberAccessNode->AccessedFunction->Has<SampledImageIntrinsicFunctionAttribute>();
  ReturnIf(intrinsicAttribute == nullptr, , "Failed to find the pre-parsed intrinsic information");

  ZilchShaderIRType* returnType = translator->mLibrary->FindType(functionCallNode->ResultType);
  Array<IZilchShaderIR*> arguments;
  translator->GetFunctionCallArguments(functionCallNode, (IZilchShaderIR*)nullptr, arguments, context);

  // When the first parameter is a sampled image, simply output the arguments as we received them doing no special remapping
  ZilchShaderIROp* op = translator->BuildIROpNoBlockAdd(intrinsicAttribute->mOpType, returnType, context);
  WriteArguments(translator, *intrinsicAttribute, op, arguments, 0, context);
}

void SampledImageIntrinsicFunctionResolver::TranslateSplitSampledImageIntrinsic(ZilchSpirVFrontEnd* translator, Zilch::FunctionCallNode* functionCallNode, Zilch::MemberAccessNode* memberAccessNode, ZilchSpirVFrontEndContext* context)
{
  SampledImageIntrinsicFunctionAttribute* intrinsicAttribute = memberAccessNode->AccessedFunction->Has<SampledImageIntrinsicFunctionAttribute>();
  ReturnIf(intrinsicAttribute == nullptr, , "Failed to find the pre-parsed intrinsic information");

  ZilchShaderIRType* returnType = translator->mLibrary->FindType(functionCallNode->ResultType);
  Array<IZilchShaderIR*> arguments;
  translator->GetFunctionCallArguments(functionCallNode, (IZilchShaderIR*)nullptr, arguments, context);

  // When the signature is a split image and sampler, we have to first combine the two parameters together.
  // In an idea world we could just force the user to do this and write this all in script,
  // however a sampled image cannot be stored into a variable, it must stay as a value type.
  // So we have to do build the sampled image with some heavy handed intrinsics.
  ZilchShaderIROp* imageOp = translator->GetOrGenerateValueTypeFromIR(arguments[0], context);
  ZilchShaderIROp* samplerOp = translator->GetOrGenerateValueTypeFromIR(arguments[1], context);
  ZilchShaderIRImageType imageType;
  ErrorIf(!imageType.Load(imageOp->mResultType), "This should never happen as it's validated during attribute parsing");

  // This is one of the really odd things about intrinsic primitives and functions. We have to get the sampled image
  // type of the image + sampler, but this could be entirely defined in script so we can't easily look it up.
  // This is also something we want to consistently define only once, so to do this we generate a unique name for
  // this type and either find or create it. If the user also created this type, then the backend deduplication
  // will handle mapping the types to the same spirv type.
  String sampledImageName = String::Format("SampledImage_%s_%d_%d_%d_%d_%d_%d", imageType.GetSampledType()->mName.c_str(), imageType.GetDim(), imageType.GetDepth(), imageType.GetArrayed(), imageType.GetMultiSampled(), imageType.GetSampled(), imageType.GetFormat());
  ZilchShaderIRType* sampledImageType = translator->mLibrary->FindType(sampledImageName);
  if(sampledImageType == nullptr)
  {
    sampledImageType = translator->MakeTypeAndPointer(translator->mLibrary, ShaderIRTypeBaseType::SampledImage, sampledImageName, nullptr, spv::StorageClassUniformConstant);
    sampledImageType->mParameters.PushBack(imageOp->mResultType);
    ShaderIRTypeMeta* samplerTypeMeta = translator->MakeShaderTypeMeta(sampledImageType, nullptr);
    samplerTypeMeta->mIsIntrinsicType = true;
  }

  ZilchShaderIROp* sampledImageOp = translator->BuildIROp(context->mCurrentBlock, OpType::OpSampledImage, sampledImageType, imageOp, samplerOp, context);
  ZilchShaderIROp* op = translator->BuildIROpNoBlockAdd(intrinsicAttribute->mOpType, returnType, context);
  // Replace the image + sampler with the sampled image then write out the rest of the args
  op->mArguments.PushBack(sampledImageOp);
  WriteArguments(translator, *intrinsicAttribute, op, arguments, 2, context);
}

void SampledImageIntrinsicFunctionResolver::WriteArguments(ZilchSpirVFrontEnd* translator, SampledImageIntrinsicFunctionAttribute& intrinsicAttribute, ZilchShaderIROp* op, Array<IZilchShaderIR*>& arguments, size_t startIndex, ZilchSpirVFrontEndContext* context)
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
