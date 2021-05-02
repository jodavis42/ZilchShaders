///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "SampledImagePrimitiveResolver.hpp"
#include "Enums/ImageEnums.hpp"

namespace Zero
{

//-------------------------------------------------------------------SampledImagePrimitiveAttribute
bool SampledImagePrimitiveAttribute::Parse(ZilchSpirVFrontEnd* translator, ShaderIRAttribute& attribute)
{
  mImageType = nullptr;

  ZilchShaderIRLibrary* shaderLibrary = translator->mLibrary;
  for(size_t i = 0; i < attribute.mParameters.Size(); ++i)
  {
    ShaderIRAttributeParameter& attributeParam = attribute.mParameters[i];
    String attributeParamName = attributeParam.GetName();

    if(attributeParamName == "imageType")
    {
      Zilch::Type* zilchImageType = attributeParam.GetTypeValue();
      if(attributeParam.GetType() != Zilch::ConstantType::Type || zilchImageType == nullptr)
      {
        String msg = String::Format("Parameter '%s' must be the typeid of an image type.", attributeParamName.c_str());
        translator->SendTranslationError(attributeParam.GetLocation(), msg);
        return false;
      }

      mImageType = shaderLibrary->FindType(zilchImageType);
      ZilchShaderIRImageType shaderImageType;
      if(!shaderImageType.Load(mImageType))
      {
        mImageType = nullptr;
        String msg = String::Format("Type '%s' isn't valid for the attribute [%s].", zilchImageType->ToString().c_str(), attribute.mAttributeName.c_str());
        translator->SendTranslationError(attributeParam.GetLocation(), msg);
        return false;
      }
    }
    else
    {
      String msg = String::Format("Parameter '%s' is not valid on attribute %s.", attributeParamName.c_str(), attribute.mAttributeName.c_str());
      translator->SendTranslationError(attributeParam.GetLocation(), msg);
      return false;
    }
  }
  return true;
}

//-------------------------------------------------------------------SampledImagePrimitiveResolver
float SampledImagePrimitiveResolver::GetPriority() const
{
  return static_cast<float>(BasePriorities::SampledImage);
}

void SampledImagePrimitiveResolver::Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute)
{
  Zilch::ClassNode* classNode = Zilch::Type::DynamicCast< Zilch::ClassNode*>(node);
  if(classNode == nullptr)
  {
    String msg = String::Format("Attribute [%s] is only valid on structs.", translator->mSettings->mNameSettings.mSampledImagePrimitiveAttribute.c_str());
    translator->SendTranslationError(attribute.GetLocation(), msg);
    return;
  }

  SampledImagePrimitiveAttribute primitiveAttribute;
  if(!primitiveAttribute.Parse(translator, attribute))
    return;

  ZilchShaderIRLibrary* shaderLibrary = translator->mLibrary;
  // Fix the shader type, pointer, and meta to reflect what's needed for an image.
  ZilchShaderIRType* sampledImageType = shaderType;
  shaderType->mBaseType = ShaderIRTypeBaseType::SampledImage;
  shaderType->mPointerType->mStorageClass = spv::StorageClassUniformConstant;
  shaderType->mMeta->mIsIntrinsicType = true;
  sampledImageType->mParameters.PushBack(primitiveAttribute.mImageType);

  attributes.AddAttribute(SpirVNameSettings::mNonCopyableAttributeName, nullptr);
  // Mark the required storage class on this type. Used in the front end translation.
  ShaderIRAttribute* storageAttribute = attributes.AddAttribute(SpirVNameSettings::mStorageClassAttribute, nullptr);
  ShaderIRAttributeParameter& param = storageAttribute->mParameters.PushBack();
  param.SetIntValue(spv::StorageClassUniformConstant);
}

}//namespace Zero
