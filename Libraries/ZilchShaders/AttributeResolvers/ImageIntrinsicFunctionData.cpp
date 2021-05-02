///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "ImageIntrinsicFunctionData.hpp"
#include "ZilchShaders/AttributeResolvers/AttributeParsingUtilities.hpp"

namespace Zero
{

//-------------------------------------------------------------------ImageIntrinsicFunctionData
bool ImageIntrinsicFunctionData::Parse(ZilchSpirVFrontEnd* translator, ShaderIRAttribute& attribute)
{
  mOpName = String();
  mOpType = OpType::OpNop;
  mOperands = ImageOperands::None;
  mOperandsLocation = -1;

  ZilchShaderIRLibrary* shaderLibrary = translator->mLibrary;
  for(size_t i = 0; i < attribute.mParameters.Size(); ++i)
  {
    ShaderIRAttributeParameter& attributeParam = attribute.mParameters[i];
    String attributeParamName = attributeParam.GetName();
    if(attributeParamName == "opName")
      AttributeParsingUtilities::ReadOpName(translator, attributeParam, mOpName, mOpType);
    else if(attributeParamName == "operands")
      mOperands = AttributeParsingUtilities::ReadEnumValidated<ImageOperands::Enum>(translator, attributeParam);
    else if(attributeParamName == "operandsLocation")
      mOperandsLocation = AttributeParsingUtilities::ReadIntegerValidated(translator, attributeParam);
    else
    {
      String msg = String::Format("Parameter '%s' is not valid on attribute [%s].", attributeParamName.c_str(), attribute.mAttributeName.c_str());
      translator->SendTranslationError(attributeParam.GetLocation(), msg);
      return false;
    }
    if(translator->mErrorTriggered)
      return false;
  }

  return true;
}

}//namespace Zero
