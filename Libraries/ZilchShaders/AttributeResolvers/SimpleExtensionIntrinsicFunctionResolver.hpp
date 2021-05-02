///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ZilchShadersStandard.hpp"

#include "ZilchShaders/AttributeResolvers/IAttributeResolver.hpp"

namespace Zero
{

//-------------------------------------------------------------------SimpleExtensionIntrinsicFunctionAttribute
/// Helper utility to parse and validate the [SimpleExtensionIntrinsicFunction] attribute.
class SimpleExtensionIntrinsicFunctionAttribute
{
public:
  ZilchDeclareType(SimpleExtensionIntrinsicFunctionAttribute, Zilch::TypeCopyMode::ReferenceType);
  bool Parse(ZilchSpirVFrontEnd* translator, ShaderIRAttribute& attribute);

  String mExtensionName;
  String mOpName;
  int mOpType;
  SpirVExtensionLibrary* mExtensionLibrary = nullptr;
};

//-------------------------------------------------------------------SimpleExtensionIntrinsicFunctionResolver
/// Handles creating a simple extension intrinsic function. A simple intrinsic is defined
/// as one where all operands are value types (no pointer types).
class SimpleExtensionIntrinsicFunctionResolver : public IAttributeResolver
{
public:
  void Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute) override;

private:
  static void Translate(ZilchSpirVFrontEnd* translator, Zilch::FunctionCallNode* functionCallNode, Zilch::MemberAccessNode* memberAccessNode, ZilchShaderExtensionImport* importLibraryIR, ZilchSpirVFrontEndContext* context);
};

}//namespace Zero