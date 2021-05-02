///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ZilchShadersStandard.hpp"

#include "ZilchShaders/AttributeResolvers/IAttributeResolver.hpp"

namespace Zero
{

//-------------------------------------------------------------------SimpleIntrinsicFunctionAttribute
/// Helper utility to parse and validate the [SimpleIntrinsicFunction] attribute.
class SimpleIntrinsicFunctionAttribute
{
public:
  ZilchDeclareType(SimpleIntrinsicFunctionAttribute, Zilch::TypeCopyMode::ReferenceType);
  bool Parse(ZilchSpirVFrontEnd* translator, ShaderIRAttribute& attribute);

  String mOpName;
  OpType mOpType;
};

//-------------------------------------------------------------------SimpleIntrinsicFunctionResolver
/// Handles creating a simple intrinsic function. A simple intrinsic is defined
/// as one where all operands are value types (no pointer types).
class SimpleIntrinsicFunctionResolver : public IAttributeResolver
{
public:
  void Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute) override;

private:
  static void Translate(ZilchSpirVFrontEnd* translator, Zilch::FunctionCallNode* functionCallNode, Zilch::MemberAccessNode* memberAccessNode, ZilchSpirVFrontEndContext* context);
};

}//namespace Zero