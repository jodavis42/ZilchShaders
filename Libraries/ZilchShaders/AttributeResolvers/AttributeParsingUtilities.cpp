///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "AttributeParsingUtilities.hpp"

namespace Zero
{

//-------------------------------------------------------------------AttributeParsingUtilities
bool AttributeParsingUtilities::ReadString(ZilchSpirVFrontEnd* translator, ShaderIRAttributeParameter& attributeParam, String& value)
{
  if(attributeParam.GetType() != Zilch::ConstantType::String)
  {
    String msg = String::Format("Parameter '%s' must be a string.");
    translator->SendTranslationError(attributeParam.GetLocation(), msg);
    return false;
  }

  value = attributeParam.GetStringValue();
  return true;
}

bool AttributeParsingUtilities::ReadOpName(ZilchSpirVFrontEnd* translator, ShaderIRAttributeParameter& attributeParam, String& opName, OpType& opType)
{
  SpirVDefinitions& spirVDefinitions = translator->mSettings->mSpirVDefinitions;
  if(attributeParam.GetType() != Zilch::ConstantType::String)
  {
    String msg = String::Format("Parameter '%s' must be a string.");
    translator->SendTranslationError(attributeParam.GetLocation(), msg);
    return false;
  }

  opName = attributeParam.GetStringValue();
  const SpirVInstructions::Instruction* instruction = spirVDefinitions.mInstructions.FindInstruction(opName);
  if(instruction == nullptr)
  {
    String msg = String::Format("OpName '%s' is not a valid spirv op code", opName);
    translator->SendTranslationError(attributeParam.GetLocation(), msg);
    return false;
  }
  opType = (OpType)instruction->mOpCode;
  return true;
}

int AttributeParsingUtilities::ReadEnumValidated(ZilchSpirVFrontEnd* translator, ShaderIRAttributeParameter& attributeParam, Zilch::BoundType* enumType)
{
  if(attributeParam.GetType() != Zilch::ConstantType::Enumeration || attributeParam.GetTypeValue() != enumType)
  {
    String msg = String::Format("Parameter '%s' must be of type '%s'.", attributeParam.GetName().c_str(), enumType->Name.c_str());
    translator->SendTranslationError(attributeParam.GetLocation(), msg);
    return 0;
  }
  return attributeParam.GetIntValue();
}

int AttributeParsingUtilities::ReadIntegerValidated(ZilchSpirVFrontEnd* translator, ShaderIRAttributeParameter& attributeParam)
{
  if(attributeParam.GetType() != Zilch::ConstantType::Integer)
  {
    String msg = String::Format("Parameter '%s' must be an integer.");
    translator->SendTranslationError(attributeParam.GetLocation(), msg);
    return false;
  }
  return attributeParam.GetIntValue();
}

Zilch::Type* AttributeParsingUtilities::GetOwningType(ZilchSpirVFrontEnd* translator, ZilchShaderIRType* currentType, ShaderIRAttributeList& attributes)
{
  ZilchShaderIRLibrary* library = translator->mLibrary;
  Zilch::Type* owningType = currentType->mZilchType;
  // Handle extension attributes by replacing the "owning type" for the function resolver if needed
  ShaderIRAttribute* extensionAttribute = attributes.FindFirstAttribute(translator->mSettings->mNameSettings.mExtensionAttribute);
  if(extensionAttribute != nullptr)
  {
    owningType = extensionAttribute->mParameters[0].GetTypeValue();
    if(owningType == nullptr)
      translator->SendTranslationError(extensionAttribute->GetLocation(), "Invalid extension type attribute");
  }
  return owningType;
}

}//namespace Zero
