///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ZilchShadersStandard.hpp"
#include "Enums/ImageEnums.hpp"

namespace Zero
{

//-------------------------------------------------------------------AttributeParsingUtilities
class AttributeParsingUtilities
{
public:
  static bool ReadString(ZilchSpirVFrontEnd* translator, ShaderIRAttributeParameter& attributeParam, String& value);
  static bool ReadOpName(ZilchSpirVFrontEnd* translator, ShaderIRAttributeParameter& attributeParam, String& opName, OpType& opType);
  static int ReadEnumValidated(ZilchSpirVFrontEnd* translator, ShaderIRAttributeParameter& attributeParam, Zilch::BoundType* enumType);
  static int ReadIntegerValidated(ZilchSpirVFrontEnd* translator, ShaderIRAttributeParameter& attributeParam);

  template <typename EnumType>
  static EnumType ReadEnumValidated(ZilchSpirVFrontEnd* translator, ShaderIRAttributeParameter& attributeParam)
  {
    return (EnumType)ReadEnumValidated(translator, attributeParam, ZilchTypeId(EnumType));
  }

  static Zilch::Type* GetOwningType(ZilchSpirVFrontEnd* translator, ZilchShaderIRType* currentType, ShaderIRAttributeList& attributes);
};

}//namespace Zero