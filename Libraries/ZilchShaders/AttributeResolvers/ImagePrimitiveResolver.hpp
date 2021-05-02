///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ZilchShadersStandard.hpp"
#include "ZilchShaders/Enums/ImageEnums.hpp"
#include "ZilchShaders/AttributeResolvers/IAttributeResolver.hpp"

namespace Zero
{

//-------------------------------------------------------------------ImagePrimitiveAttribute
/// Helper utility to parse and validate the [ImagePrimitive] attribute.
class ImagePrimitiveAttribute
{
public:
  bool Parse(ZilchSpirVFrontEnd* translator, ShaderIRAttribute& attribute);

  ZilchShaderIRType* mSampledType = nullptr;
  ImageDimension::Enum mDimension = ImageDimension::Dim2D;
  ImageDepthMode::Enum mDepthMode = ImageDepthMode::None;
  ImageArrayedMode::Enum mArrayedMode = ImageArrayedMode::None;
  ImageMultiSampledMode::Enum mMultiSampledMode = ImageMultiSampledMode::SingleSampled;
  ImageSampledMode::Enum mSampledMode = ImageSampledMode::Sampling;
  ImageFormat::Enum mImageFormat = ImageFormat::Unknown;
};

//-------------------------------------------------------------------ImagePrimitiveResolver
/// Handles creating an image primitive type from an attribute.
class ImagePrimitiveResolver : public IAttributeResolver
{
public:
  float GetPriority() const override;
  void Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute) override;
};

}//namespace Zero
