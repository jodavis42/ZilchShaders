///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

// Simple struct that defines a shader by name and a collection of fragments on that shader
struct ShaderDefinition
{
  String mShaderName;
  Array<String> mFragmentNames;
};

struct ErrorSettings
{
  ErrorSettings()
  {
    mErrorOnNoMain = false;
  }
  bool mErrorOnNoMain;
};

void BuildZilchProject(StringParam path, Zilch::Project& project);
Zilch::LibraryRef BuildZilchLibrary(Zilch::Project& project, StringParam libraryName, Zilch::Module& zilchDependencies);
void LoadZilchScriptShaderDefinitions(ZilchShaderTestConfiguration& testConfig, Array<ShaderDefinition>& shadersDefs, StringParam path);
void LoadZilchScriptErrorSettings(ErrorSettings& errorSettings, StringParam path);
