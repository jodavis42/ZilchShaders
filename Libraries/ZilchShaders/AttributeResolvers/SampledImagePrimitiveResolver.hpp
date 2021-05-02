///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ZilchShadersStandard.hpp"

#include "ZilchShaders/AttributeResolvers/IAttributeResolver.hpp"

namespace Zero
{

//-------------------------------------------------------------------SampledImagePrimitiveAttribute
/// Helper utility to parse and validate the [SampledImagePrimitive] attribute.
class SampledImagePrimitiveAttribute
{
public:
  bool Parse(ZilchSpirVFrontEnd* translator, ShaderIRAttribute& attribute);

  ZilchShaderIRType* mImageType = nullptr;
};

//-------------------------------------------------------------------SampledImagePrimitiveResolver
/// Handles creating an image primitive type from an attribute.
class SampledImagePrimitiveResolver : public IAttributeResolver
{
public:
  float GetPriority() const override;
  void Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute) override;
};

}//namespace Zero