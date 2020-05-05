///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Zero
{

//-------------------------------------------------------------------ShaderIRAttributeParameter
class ShaderIRAttributeParameter
{
public:
  ShaderIRAttributeParameter();
  ShaderIRAttributeParameter(Zilch::AttributeParameter& param, Zilch::SyntaxNode* node);

  String GetName() const;
  void SetName(StringParam name);

  Zilch::ConstantType::Enum GetType() const;

  String GetStringValue() const;
  void SetStringValue(StringParam stringValue);

  int GetIntValue() const;
  void SetIntValue(int intValue);

  float GetFloatValue() const;
  void SetFloatValue(float floatValue);

  Zilch::Type* GetTypeValue() const;
  void SetTypeValue(Zilch::Type* typeValue);

  Zilch::CodeLocation* GetLocation();
  void SetLocationNode(Zilch::SyntaxNode* node);

  // Return the internal zilch attribute parameter. Mostly exposed for ease of binding.
  Zilch::AttributeParameter& GetZilchAttributeParameter();

private:
  Zilch::AttributeParameter mParameter;
  Zilch::SyntaxNode* mNode;
};

//-------------------------------------------------------------------ShaderIRAttribute
class ShaderIRAttribute
{
public:
  ShaderIRAttribute();
  ShaderIRAttribute(StringParam attributeName, Zilch::SyntaxNode* locationNode);

  ShaderIRAttributeParameter* FindFirstParameter(StringParam name);
  Zilch::CodeLocation* GetLocation();

  String mAttributeName;
  Array<ShaderIRAttributeParameter> mParameters;
  Zilch::SyntaxNode* mNode;

  // Was this attribute created from another (e.g. [Input] implies [AppBuiltInInput]).
  // Some errors are only valid if the attribute was explicitly declared.
  bool mImplicitAttribute;
};

//-------------------------------------------------------------------ShaderIRAttributeList
class ShaderIRAttributeList
{
public:
  typedef Array<ShaderIRAttribute>::range Range;

  class NamedRange
  {
  public:
    NamedRange();
    NamedRange(StringParam attributeToFind, const Range& range);

    ShaderIRAttribute* Front();
    bool Empty() const;
    void PopFront();

  private:
    void SkipAttributes();

    String mAttributeToFind;
    Range mRange;
  };

  ShaderIRAttribute* AddAttribute(StringParam attributeName, Zilch::AttributeNode* node);
  NamedRange FindAttributes(StringParam attributeName);
  ShaderIRAttribute* FindFirstAttribute(StringParam attributeName);
  Range All();
  size_t Size();

  ShaderIRAttribute* GetAtIndex(size_t index);
  ShaderIRAttribute* operator[](size_t index);

private:
  Array<ShaderIRAttribute> mAttributes;
};

}//namespace Zero
