///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "ImagePrimitiveResolver.hpp"
#include "ZilchShaders/AttributeResolvers/AttributeParsingUtilities.hpp"

namespace Zero
{

//-------------------------------------------------------------------ImagePrimitiveAttribute
bool ImagePrimitiveAttribute::Parse(ZilchSpirVFrontEnd* translator, ShaderIRAttribute& attribute)
{
  mSampledType = nullptr;
  mDimension = ImageDimension::Dim2D;
  mDepthMode = ImageDepthMode::None;
  mArrayedMode = ImageArrayedMode::None;
  mMultiSampledMode = ImageMultiSampledMode::SingleSampled;
  mSampledMode = ImageSampledMode::Sampling;
  mImageFormat = ImageFormat::Unknown;

  ZilchShaderIRLibrary* shaderLibrary = translator->mLibrary;
  for(size_t i = 0; i < attribute.mParameters.Size(); ++i)
  {
    ShaderIRAttributeParameter& attributeParam = attribute.mParameters[i];
    String attributeParamName = attributeParam.GetName();
    if(attributeParamName == "sampledType")
    {
      Zilch::Type* zilchSampledType = attributeParam.GetTypeValue();
      if(attributeParam.GetType() != Zilch::ConstantType::Type || zilchSampledType == nullptr)
      {
        String msg = String::Format("Parameter '%s' must be the typeid of a type.", attributeParamName.c_str());
        translator->SendTranslationError(attributeParam.GetLocation(), msg);
        return false;
      }

      mSampledType = shaderLibrary->FindType(zilchSampledType);
      if(mSampledType == nullptr || !(mSampledType->mBaseType == ShaderIRTypeBaseType::Void || mSampledType->mBaseType == ShaderIRTypeBaseType::Int || mSampledType->mBaseType == ShaderIRTypeBaseType::Float))
      {
        mSampledType = nullptr;
        String msg = String::Format("Type '%s' isn't valid for the attribute [%s]. It must be either Void, Integer, or Real", zilchSampledType->ToString().c_str(), attribute.mAttributeName.c_str());
        translator->SendTranslationError(attributeParam.GetLocation(), msg);
        return false;
      }
    }
    else if(attributeParamName == "dimension")
      mDimension = AttributeParsingUtilities::ReadEnumValidated<ImageDimension::Enum>(translator, attributeParam);
    else if(attributeParamName == "depthMode")
      mDepthMode = AttributeParsingUtilities::ReadEnumValidated<ImageDepthMode::Enum>(translator, attributeParam);
    else if(attributeParamName == "arrayedMode")
      mArrayedMode = AttributeParsingUtilities::ReadEnumValidated<ImageArrayedMode::Enum>(translator, attributeParam);
    else if(attributeParamName == "multiSampledMode")
      mMultiSampledMode = AttributeParsingUtilities::ReadEnumValidated<ImageMultiSampledMode::Enum>(translator, attributeParam);
    else if(attributeParamName == "sampledMode")
      mSampledMode = AttributeParsingUtilities::ReadEnumValidated<ImageSampledMode::Enum>(translator, attributeParam);
    else if(attributeParamName == "imageFormat")
      mImageFormat = AttributeParsingUtilities::ReadEnumValidated<ImageFormat::Enum>(translator, attributeParam);
    else
    {
      String msg = String::Format("Parameter '%s' is not valid on attribute [%s].", attributeParamName.c_str(), attribute.mAttributeName.c_str());
      translator->SendTranslationError(attributeParam.GetLocation(), msg);
      return false;
    }
    if(translator->mErrorTriggered)
      return false;
  }

  return true;
}

//-------------------------------------------------------------------ImagePrimitiveResolver
float ImagePrimitiveResolver::GetPriority() const
{
  return static_cast<float>(IAttributeResolver::BasePriorities::Image);
}

void ImagePrimitiveResolver::Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute)
{
  Zilch::ClassNode* classNode = Zilch::Type::DynamicCast< Zilch::ClassNode*>(node);
  if(classNode == nullptr)
  {
    String msg = String::Format("Attribute [%s] is only valid on structs.", translator->mSettings->mNameSettings.mImagePrimitiveAttribute.c_str());
    translator->SendTranslationError(attribute.GetLocation(), msg);
    return;
  }
  
  ImagePrimitiveAttribute primitiveAttribute;
  if(!primitiveAttribute.Parse(translator, attribute))
    return;

  ZilchShaderIRLibrary* shaderLibrary = translator->mLibrary;
  // Create the base image type for a sampled image
  Zilch::BoundType* zilchImageType = classNode->Type;
  ZilchShaderIRType* imageType = shaderType;
  // Fix the shader type, pointer, and meta to reflect what's needed for an image.
  shaderType->mBaseType = ShaderIRTypeBaseType::Image;
  shaderType->mPointerType->mStorageClass = spv::StorageClassUniformConstant;
  shaderType->mMeta->mIsIntrinsicType = true;
  imageType->mParameters.PushBack(primitiveAttribute.mSampledType);
  imageType->mParameters.PushBack(translator->GetOrCreateConstantIntegerLiteral(primitiveAttribute.mDimension));
  imageType->mParameters.PushBack(translator->GetOrCreateConstantIntegerLiteral(primitiveAttribute.mDepthMode));
  imageType->mParameters.PushBack(translator->GetOrCreateConstantIntegerLiteral(primitiveAttribute.mArrayedMode));
  imageType->mParameters.PushBack(translator->GetOrCreateConstantIntegerLiteral(primitiveAttribute.mMultiSampledMode));
  imageType->mParameters.PushBack(translator->GetOrCreateConstantIntegerLiteral(primitiveAttribute.mSampledMode));
  imageType->mParameters.PushBack(translator->GetOrCreateConstantIntegerLiteral(primitiveAttribute.mImageFormat));
  
  attributes.AddAttribute(SpirVNameSettings::mNonCopyableAttributeName, nullptr);
  // Mark the required storage class on this type. Used in the front end translation.
  ShaderIRAttribute* storageAttribute = attributes.AddAttribute(SpirVNameSettings::mStorageClassAttribute, nullptr);
  ShaderIRAttributeParameter& param = storageAttribute->mParameters.PushBack();
  param.SetIntValue(spv::StorageClassUniformConstant);
}

}//namespace Zero
