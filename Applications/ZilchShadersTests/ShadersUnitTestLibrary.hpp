///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis 
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ShadersUnitTestLibrary.hpp"
#include "Common/Containers/Array.hpp"
#include "Common/Containers/BlockArray.hpp"

using Zero::PodBlockArray;

//-------------------------------------------------------------------ZilchShaderFragmentCollection
struct ZilchShaderFragmentCollection
{
  ZilchDeclareType(ZilchShaderFragmentCollection, Zilch::TypeCopyMode::ReferenceType);

  void Add(StringParam& fragmentName);
  void Clear();

  Array<String> mFragmentNames;
};

//-------------------------------------------------------------------ZilchShaderDefinition
struct ZilchShaderDefinition
{
  ZilchDeclareType(ZilchShaderDefinition, Zilch::TypeCopyMode::ReferenceType);

  ZilchShaderFragmentCollection* GetFragments();

  String mShaderName;
  ZilchShaderFragmentCollection mFragments;
};

//-------------------------------------------------------------------ZilchShaderCollection
struct ZilchShaderCollection
{
  ZilchDeclareType(ZilchShaderCollection, Zilch::TypeCopyMode::ReferenceType);
  ZilchShaderDefinition* AddShader();
  Array<ZilchShaderDefinition> mShaders;
};

//-------------------------------------------------------------------ZilchShaderErrorSettings
struct ZilchShaderTestErrorSettings
{
  ZilchDeclareType(ZilchShaderTestErrorSettings, Zilch::TypeCopyMode::ReferenceType);

  ZilchShaderTestErrorSettings();
  bool mErrorOnNoMain;
};

//-------------------------------------------------------------------ZilchShaderTestConfiguration
struct ZilchShaderTestConfiguration
{
  ZilchDeclareType(ZilchShaderTestConfiguration, Zilch::TypeCopyMode::ReferenceType);

  ZilchShaderTestConfiguration();

  String mCurrentDirectory;
  bool mTestComposites;
};

ZilchDeclareStaticLibrary(ShaderTestLibrary, ZilchNoNamespace, ZeroNoImportExport);
