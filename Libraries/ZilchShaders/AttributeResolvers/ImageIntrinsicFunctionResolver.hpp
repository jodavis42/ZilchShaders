///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ZilchShadersStandard.hpp"
#include "ZilchShaders/AttributeResolvers/ImageIntrinsicFunctionData.hpp"
#include "ZilchShaders/AttributeResolvers/IAttributeResolver.hpp"

namespace Zero
{

//-------------------------------------------------------------------ImageIntrinsicFunctionAttribute
/// Specifies an intrinsic function for an image. Image intrinsics are more complicated as they may take a mask
/// that controls what extra parameters exist. This mask isn't always at a consistent location like the end of the function either,
/// so the location was added for user control. The location specifies what function argument this should be placed before,
/// so if location is 2 and there are 3 arguments then it's: [arg0, arg1, operandsMask, arg2].
/// If no mask and location are specified, then no mask is written (not all intrinsics specify a mask either).
/// A Image intrinsic function expects the first parameter to either be an image or a sampled image.
class ImageIntrinsicFunctionAttribute : public ImageIntrinsicFunctionData
{
public:
  ZilchDeclareType(ImageIntrinsicFunctionAttribute, Zilch::TypeCopyMode::ReferenceType);
};

//-------------------------------------------------------------------ImageIntrinsicFunctionResolver
/// Handles creating an image intrinsic function from an attribute.
class ImageIntrinsicFunctionResolver : public IAttributeResolver
{
public:
  void Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute) override;

private:
  static void TranslateImageIntrinsic(ZilchSpirVFrontEnd* translator, Zilch::FunctionCallNode* functionCallNode, Zilch::MemberAccessNode* memberAccessNode, ZilchSpirVFrontEndContext* context);
  static void TranslateSampledImageIntrinsic(ZilchSpirVFrontEnd* translator, Zilch::FunctionCallNode* functionCallNode, Zilch::MemberAccessNode* memberAccessNode, ZilchSpirVFrontEndContext* context);
  static void WriteArguments(ZilchSpirVFrontEnd* translator, ImageIntrinsicFunctionAttribute& intrinsicAttribute, ZilchShaderIROp* op, Array<IZilchShaderIR*>& arguments, size_t startIndex, ZilchSpirVFrontEndContext* context);
};

}//namespace Zero