///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "SamplerPrimitiveResolver.hpp"

namespace Zero
{

//-------------------------------------------------------------------SamplerPrimitiveResolver
void SamplerPrimitiveResolver::Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute)
{
  Zilch::ClassNode* classNode = Zilch::Type::DynamicCast< Zilch::ClassNode*>(node);
  if(classNode == nullptr)
  {
    String msg = String::Format("Attribute [%s] is only valid on structs.", translator->mSettings->mNameSettings.mSamplerPrimitiveAttribute.c_str());
    translator->SendTranslationError(attribute.GetLocation(), msg);
    return;
  }

  ZilchShaderIRLibrary* shaderLibrary = translator->mLibrary;
  Zilch::BoundType* zilchSamplerType = classNode->Type;
  // Fix the shader type, pointer, and meta to reflect what's needed for a sampler.
  ZilchShaderIRType* samplerType = shaderType;
  shaderType->mBaseType = ShaderIRTypeBaseType::Sampler;
  shaderType->mPointerType->mStorageClass = spv::StorageClassUniformConstant;
  shaderType->mMeta->mIsIntrinsicType = true;

  attributes.AddAttribute(SpirVNameSettings::mNonCopyableAttributeName, nullptr);
  // Mark the required storage class on this type. Used in the front end translation.
  ShaderIRAttribute* storageAttribute = attributes.AddAttribute(SpirVNameSettings::mStorageClassAttribute, nullptr);
  ShaderIRAttributeParameter& param = storageAttribute->mParameters.PushBack();
  param.SetIntValue(spv::StorageClassUniformConstant);
}

}//namespace Zero
