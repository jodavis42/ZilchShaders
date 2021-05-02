///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "SimpleExtensionIntrinsicFunctionResolver.hpp"
#include "ZilchShaders/AttributeResolvers/AttributeParsingUtilities.hpp"

namespace Zero
{

//-------------------------------------------------------------------SimpleExtensionIntrinsicFunctionAttribute
ZilchDefineType(SimpleExtensionIntrinsicFunctionAttribute, builder, type)
{
  ZilchBindDefaultCopyDestructor();
  type->CreatableInScript = false;
}

bool SimpleExtensionIntrinsicFunctionAttribute::Parse(ZilchSpirVFrontEnd* translator, ShaderIRAttribute& attribute)
{
  mOpName = String();
  mOpType = OpType::OpNop;
  ZilchShaderIRLibrary* shaderLibrary = translator->mLibrary;
  for(size_t i = 0; i < attribute.mParameters.Size(); ++i)
  {
    ShaderIRAttributeParameter& attributeParam = attribute.mParameters[i];
    String attributeParamName = attributeParam.GetName();

    if(attributeParamName == "extensionName")
    {
      AttributeParsingUtilities::ReadString(translator, attributeParam, mExtensionName);
    }
    else if(attributeParamName == "opName")
    {
      AttributeParsingUtilities::ReadString(translator, attributeParam, mOpName);
    }
    else
    {
      String msg = String::Format("Parameter '%s' is not valid on attribute %s.", attributeParamName.c_str(), attribute.mAttributeName.c_str());
      translator->SendTranslationError(attributeParam.GetLocation(), msg);
      return false;
    }
  }

  // Load the extension library (must already exist)
  SpirVExtensionLibrary* extLibrary = shaderLibrary->FindExtensionLibrary(mExtensionName);
  if(extLibrary == nullptr)
  {
    String msg = String::Format("Failed to extension library '%s'", mExtensionName.c_str());
    translator->SendTranslationError(attribute.GetLocation(), msg);
    return false;
  }
  mExtensionLibrary = extLibrary;
  
  // Convert the op name to the op code
  SpirVInstructions* extensionInstructions = translator->mSettings->mSpirVDefinitions.mExtensionInstructions.FindPointer(mExtensionName);
  if(extensionInstructions == nullptr)
  {
    String msg = String::Format("Failed to extension library '%s'", mExtensionName.c_str());
    translator->SendTranslationError(attribute.GetLocation(), msg);
    return false;
  }

  const SpirVInstructions::Instruction* instruction = extensionInstructions->FindInstruction(mOpName);
  if(instruction == nullptr)
  {
    String msg = String::Format("Failed to find translation for opName '%s'", mOpName.c_str());
    translator->SendTranslationError(attribute.GetLocation(), msg);
    return false;
  }
  mOpType = instruction->mOpCode;

  return true;
}

//-------------------------------------------------------------------SimpleExtensionIntrinsicFunctionResolver
void SimpleExtensionIntrinsicFunctionResolver::Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute)
{
  Zilch::FunctionNode* fnNode = Zilch::Type::DynamicCast< Zilch::FunctionNode*>(node);
  if(fnNode == nullptr)
  {
    String msg = String::Format("Attribute [%s] is only valid on functions.", translator->mSettings->mNameSettings.mSimpleIntrinsicFunctionAttribute.c_str());
    translator->SendTranslationError(attribute.GetLocation(), msg);
    return;
  }

  // Validate and parse the attribute
  Zilch::HandleOf<SimpleExtensionIntrinsicFunctionAttribute> intrinsicAttribute = ZilchAllocate(SimpleExtensionIntrinsicFunctionAttribute);
  if(!intrinsicAttribute->Parse(translator, attribute))
    return;
  
  // Handle extension attributes by replacing the "owning type" for the function resolver if needed
  Zilch::Type* owningType = AttributeParsingUtilities::GetOwningType(translator, shaderType, attributes);
  if(owningType == nullptr)
    return;

  intrinsicAttribute->mExtensionLibrary->CreateExtInst(fnNode->DefinedFunction, Translate);
  fnNode->DefinedFunction->Add(*intrinsicAttribute);
  fnNode->DefinedFunction->AddAttribute(translator->mSettings->mNameSettings.mIntrinsicAttribute);
}

void SimpleExtensionIntrinsicFunctionResolver::Translate(ZilchSpirVFrontEnd* translator, Zilch::FunctionCallNode* functionCallNode, Zilch::MemberAccessNode* memberAccessNode, ZilchShaderExtensionImport* importLibraryIR, ZilchSpirVFrontEndContext* context)
{
  SimpleExtensionIntrinsicFunctionAttribute* intrinsicAttribute = memberAccessNode->AccessedFunction->Has<SimpleExtensionIntrinsicFunctionAttribute>();
  ReturnIf(intrinsicAttribute == nullptr, , "Failed to find the pre-parsed intrinsic information");

  ZilchShaderIRLibrary* library = translator->mLibrary;
  
  ZilchShaderIRType* returnType = translator->mLibrary->FindType(functionCallNode->ResultType);
  Array<IZilchShaderIR*> arguments;
  translator->GetFunctionCallArguments(functionCallNode, (IZilchShaderIR*)nullptr, arguments, context);

  // Emit OpExtIns ReturnType LibraryImport OpType ...
  ZilchShaderExtensionImport* libraryImport = library->FindExtensionLibraryImport(intrinsicAttribute->mExtensionLibrary);
  ZilchShaderIRConstantLiteral* instructionLiteral = translator->GetOrCreateConstantLiteral(intrinsicAttribute->mOpType);
  ZilchShaderIROp* op = translator->BuildIROpNoBlockAdd(OpType::OpExtInst, returnType, context);
  op->mArguments.PushBack(libraryImport);
  op->mArguments.PushBack(instructionLiteral);
  for(size_t i = 0; i < arguments.Size(); ++i)
    op->mArguments.PushBack(translator->GetOrGenerateValueTypeFromIR(arguments[i], context));

  context->mCurrentBlock->AddOp(op);
  context->PushIRStack(op);
}

}//namespace Zero
