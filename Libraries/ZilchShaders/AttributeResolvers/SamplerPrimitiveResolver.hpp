///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ZilchShadersStandard.hpp"

#include "ZilchShaders/AttributeResolvers/IAttributeResolver.hpp"

namespace Zero
{

//-------------------------------------------------------------------SamplerPrimitiveResolver
/// Handles creating a sampler primitive type from an attribute.
class SamplerPrimitiveResolver : public IAttributeResolver
{
public:
  void Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute) override;
};

}//namespace Zero
