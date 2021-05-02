///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "SimpleIntrinsicFunctionResolver.hpp"
#include "ZilchShaders/AttributeResolvers/AttributeParsingUtilities.hpp"

namespace Zero
{

//-------------------------------------------------------------------SimpleIntrinsicFunctionAttribute
ZilchDefineType(SimpleIntrinsicFunctionAttribute, builder, type)
{
  ZilchBindDefaultCopyDestructor();
  type->CreatableInScript = false;
}

bool SimpleIntrinsicFunctionAttribute::Parse(ZilchSpirVFrontEnd* translator, ShaderIRAttribute& attribute)
{
  mOpName = String();
  mOpType = OpType::OpNop;
  ZilchShaderIRLibrary* shaderLibrary = translator->mLibrary;
  for(size_t i = 0; i < attribute.mParameters.Size(); ++i)
  {
    ShaderIRAttributeParameter& attributeParam = attribute.mParameters[i];
    String attributeParamName = attributeParam.GetName();

    if(attributeParamName == "opName")
      AttributeParsingUtilities::ReadOpName(translator, attributeParam, mOpName, mOpType);
    else
    {
      String msg = String::Format("Parameter '%s' is not valid on attribute %s.", attributeParamName.c_str(), attribute.mAttributeName.c_str());
      translator->SendTranslationError(attributeParam.GetLocation(), msg);
      return false;
    }
  }
  return true;
}

//-------------------------------------------------------------------SimpleIntrinsicFunctionResolver
void SimpleIntrinsicFunctionResolver::Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute)
{
  Zilch::FunctionNode* fnNode = Zilch::Type::DynamicCast< Zilch::FunctionNode*>(node);
  if(fnNode == nullptr)
  {
    String msg = String::Format("Attribute [%s] is only valid on functions.", translator->mSettings->mNameSettings.mSimpleIntrinsicFunctionAttribute.c_str());
    translator->SendTranslationError(attribute.GetLocation(), msg);
    return;
  }

  // Validate and parse the attribute
  Zilch::HandleOf<SimpleIntrinsicFunctionAttribute> intrinsicAttribute = ZilchAllocate(SimpleIntrinsicFunctionAttribute);
  if(!intrinsicAttribute->Parse(translator, attribute))
    return;
  
  // Handle extension attributes by replacing the "owning type" for the function resolver if needed
  Zilch::Type* owningType = AttributeParsingUtilities::GetOwningType(translator, shaderType, attributes);
  if(owningType == nullptr)
    return;

  ZilchShaderIRLibrary* library = translator->mLibrary;
  TypeResolvers& resolvers = library->mTypeResolvers[owningType];
  resolvers.RegisterFunctionResolver(fnNode->DefinedFunction, Translate);
  // Attach the intrinsic attribute data to the function so we can look it up later
  fnNode->DefinedFunction->Add(*intrinsicAttribute);
  fnNode->DefinedFunction->AddAttribute(translator->mSettings->mNameSettings.mIntrinsicAttribute);
}

void SimpleIntrinsicFunctionResolver::Translate(ZilchSpirVFrontEnd* translator, Zilch::FunctionCallNode* functionCallNode, Zilch::MemberAccessNode* memberAccessNode, ZilchSpirVFrontEndContext* context)
{
  SimpleIntrinsicFunctionAttribute* intrinsicAttribute = memberAccessNode->AccessedFunction->Has<SimpleIntrinsicFunctionAttribute>();
  ReturnIf(intrinsicAttribute == nullptr, , "Failed to find the pre-parsed intrinsic information");

  ZilchShaderIRType* returnType = translator->mLibrary->FindType(functionCallNode->ResultType);
  Array<IZilchShaderIR*> arguments;
  translator->GetFunctionCallArguments(functionCallNode, (IZilchShaderIR*)nullptr, arguments, context);

  // When the first parameter is an image, simply output the arguments as we received them doing no special remapping
  ZilchShaderIROp* op = translator->BuildIROpNoBlockAdd(intrinsicAttribute->mOpType, returnType, context);
  for(size_t i = 0; i < arguments.Size(); ++i)
    op->mArguments.PushBack(translator->GetOrGenerateValueTypeFromIR(arguments[i], context));
  context->mCurrentBlock->AddOp(op);
  context->PushIRStack(op);
}

}//namespace Zero
