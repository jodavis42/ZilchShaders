///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "ShadersUnitTestLibrary.hpp"

//-------------------------------------------------------------------ZilchShaderFragmentCollection
ZilchDefineType(ZilchShaderFragmentCollection, builder, type)
{
  type->HandleManager = ZilchManagerId(Zilch::PointerManager);

  ZilchBindMethod(Add);
  ZilchBindMethod(Clear);
}

void ZilchShaderFragmentCollection::Add(StringParam& fragmentName)
{
  mFragmentNames.PushBack(fragmentName);
}

void ZilchShaderFragmentCollection::Clear()
{
  mFragmentNames.Clear();
}

//-------------------------------------------------------------------ZilchShaderDefinition
ZilchDefineType(ZilchShaderDefinition, builder, type)
{
  type->HandleManager = ZilchManagerId(Zilch::PointerManager);
  ZilchBindField(mShaderName);
  ZilchBindGetter(Fragments);
}

ZilchShaderFragmentCollection* ZilchShaderDefinition::GetFragments()
{
  return &mFragments;
}

//-------------------------------------------------------------------ZilchShaderCollection
ZilchDefineType(ZilchShaderCollection, builder, type)
{
  type->HandleManager = ZilchManagerId(Zilch::PointerManager);
  ZilchBindMethod(AddShader);
}

ZilchShaderDefinition* ZilchShaderCollection::AddShader()
{
  mShaders.PushBack(ZilchShaderDefinition());
  return &mShaders[mShaders.Size() - 1];
}

//-------------------------------------------------------------------ZilchShaderTestErrorSettings
ZilchDefineType(ZilchShaderTestErrorSettings, builder, type)
{
  type->HandleManager = ZilchManagerId(Zilch::PointerManager);
  ZilchBindField(mErrorOnNoMain);
}

ZilchShaderTestErrorSettings::ZilchShaderTestErrorSettings()
{
  mErrorOnNoMain = false;
}

//-------------------------------------------------------------------ZilchShaderTestConfiguration
ZilchDefineType(ZilchShaderTestConfiguration, builder, type)
{
  type->HandleManager = ZilchManagerId(Zilch::PointerManager);
  ZilchBindField(mCurrentDirectory);
  ZilchBindField(mTestComposites);
}

ZilchShaderTestConfiguration::ZilchShaderTestConfiguration()
{
  mTestComposites = false;
}

ZilchDefineStaticLibrary(ShaderTestLibrary)
{
  builder.CreatableInScriptDefault = false;

  ZilchInitializeType(ZilchShaderFragmentCollection);
  ZilchInitializeType(ZilchShaderDefinition);
  ZilchInitializeType(ZilchShaderCollection);
  ZilchInitializeType(ZilchShaderTestErrorSettings);
  ZilchInitializeType(ZilchShaderTestConfiguration);
}
