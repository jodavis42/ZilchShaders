///
/// Authors: Joshua Davis
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

bool IsZilchScript(StringParam filePath)
{
  String zilchScriptExt = "zilchscript";
  String extension = FilePath::GetExtension(filePath);
  return extension.ToLower() == zilchScriptExt;
}

void BuildZilchProject(StringParam path, Zilch::Project& project)
{
  // Load all of the zilch files in the settings directory
  FileRange fileRange(path);
  for(; !fileRange.Empty(); fileRange.PopFront())
  {
    FileEntry entry = fileRange.FrontEntry();
    if(!IsZilchScript(entry.GetFullPath()))
      continue;
    String filePath = entry.GetFullPath();
    String fileExt = FilePath::GetExtension(filePath);
    project.AddCodeFromFile(filePath, nullptr);
  }
}

Zilch::LibraryRef BuildZilchLibrary(Zilch::Project& project, StringParam libraryName, Zilch::Module& zilchDependencies)
{
  EventConnect(&project, Zilch::Events::CompilationError, ZilchCompilerErrorCallback);

  // Compile the syntax tree
  Zilch::Array<Zilch::UserToken> tokensOut;
  Zilch::SyntaxTree syntaxTree;
  Zilch::LibraryBuilder libraryBuilder(libraryName);
  bool success = project.CompileCheckedSyntaxTree(syntaxTree, libraryBuilder, tokensOut, zilchDependencies, Zilch::EvaluationMode::Project);
  if(!success)
  {
    Error("Failed to compile settings project");
    return nullptr;
  }

  // Generate code into a library
  Zilch::CodeGenerator codeGenerator;
  return codeGenerator.Generate(syntaxTree, libraryBuilder);
}

void RunTestConfigMain(Zilch::ExecutableState* state, Zilch::BoundType* zilchType, ZilchShaderTestConfiguration& testConfig)
{
  Zilch::Core& core = Zilch::Core::GetInstance();
  Zilch::BoundType* testConfigType = ZilchTypeId(ZilchShaderTestConfiguration);
  Array<Zilch::Type*> mainParameters(ZeroInit, testConfigType);

  // Find the main function with the correct signature
  Zilch::Function* mainFunction = zilchType->FindFunction("Main", mainParameters, core.VoidType, Zilch::FindMemberOptions::None);
  if(mainFunction == nullptr)
    return;

  Zilch::ExceptionReport report;
  // Allocate the SystemValueSettings struct
  Zilch::Handle preconstructedObject = state->AllocateDefaultConstructedHeapObject(zilchType, report, Zilch::HeapFlags::NonReferenceCounted);
  
  Zilch::Call call(mainFunction, state);
  call.Set(0, &testConfig);
  call.SetHandle(Zilch::Call::This, preconstructedObject);
  call.Invoke(report);

  preconstructedObject.Delete();
}

void RunShaderCollectionMain(Zilch::ExecutableState* state, Zilch::BoundType* zilchType, ZilchShaderTestConfiguration& testConfig, Array<ShaderDefinition>& shadersDefs)
{
  Zilch::Core& core = Zilch::Core::GetInstance();
  Zilch::BoundType* testConfigType = ZilchTypeId(ZilchShaderTestConfiguration);
  Zilch::BoundType* shaderCollectionType = ZilchTypeId(ZilchShaderCollection);
  Array<Zilch::Type*> mainParameters(ZeroInit, testConfigType, shaderCollectionType);

   // Find the main function with the correct signature
  Zilch::Function* mainFunction = zilchType->FindFunction("Main", mainParameters, core.VoidType, Zilch::FindMemberOptions::None);
  if(mainFunction == nullptr)
    return;

  ZilchShaderCollection shaderCollection;
  Zilch::ExceptionReport report;
  // Allocate the SystemValueSettings struct
  Zilch::Handle preconstructedObject = state->AllocateDefaultConstructedHeapObject(zilchType, report, Zilch::HeapFlags::NonReferenceCounted);
  // Set the ShaderSystemValueSettings class as the first parameter and call the main function
  Zilch::Call call(mainFunction, state);
  call.Set(0, &testConfig);
  call.Set(1, &shaderCollection);
  call.SetHandle(Zilch::Call::This, preconstructedObject);
  call.Invoke(report);

  for(size_t i = 0; i < shaderCollection.mShaders.Size(); ++i)
  {
    ZilchShaderDefinition& loadedShaderDef = shaderCollection.mShaders[i];
    ShaderDefinition& shaderDef = shadersDefs.PushBack();
    shaderDef.mShaderName = loadedShaderDef.mShaderName;
    shaderDef.mFragmentNames = loadedShaderDef.mFragments.mFragmentNames;
  }

  preconstructedObject.Delete();
}

void LoadZilchScriptShaderDefinitions(ZilchShaderTestConfiguration& testConfig, Array<ShaderDefinition>& shadersDefs, StringParam path)
{
  Zilch::Project project;
  BuildZilchProject(path, project);

  Zilch::Module zilchDependencies;
  zilchDependencies.PushBack(ShaderTestLibrary::GetInstance().GetLibrary());
  Zilch::LibraryRef libraryRef = BuildZilchLibrary(project, "Settings", zilchDependencies);
  Zilch::Library* library = libraryRef;
  if(library == nullptr)
    return;

  // Compile the library and dependencies into an executable state
  zilchDependencies.PushBack(libraryRef);
  Zilch::ExecutableState* state = zilchDependencies.Link();

  Zilch::Core& core = Zilch::Core::GetInstance();

  testConfig.mCurrentDirectory = path;

  Zilch::BoundType* testConfigType = ZilchTypeId(ZilchShaderTestConfiguration);
  Zilch::BoundType* shaderCollectionType = ZilchTypeId(ZilchShaderCollection);
  Array<Zilch::Type*> mainParameters(ZeroInit, testConfigType, shaderCollectionType);

  for(auto range = library->BoundTypes.Values(); !range.Empty(); range.PopFront())
  {
    Zilch::BoundType* zilchType = range.Front();

    RunTestConfigMain(state, zilchType, testConfig);
    RunShaderCollectionMain(state, zilchType, testConfig, shadersDefs);
  }
}

void LoadZilchScriptErrorSettings(ErrorSettings& errorSettings, StringParam path)
{
  Zilch::Project project;
  BuildZilchProject(path, project);

  Zilch::Module zilchDependencies;
  zilchDependencies.PushBack(ShaderTestLibrary::GetInstance().GetLibrary());
  Zilch::LibraryRef libraryRef = BuildZilchLibrary(project, "Settings", zilchDependencies);
  Zilch::Library* library = libraryRef;
  if(library == nullptr)
    return;

  // Compile the library and dependencies into an executable state
  zilchDependencies.PushBack(libraryRef);
  Zilch::ExecutableState* state = zilchDependencies.Link();

  Zilch::Core& core = Zilch::Core::GetInstance();

  ZilchShaderTestConfiguration testConfig;
  testConfig.mCurrentDirectory = path;

  ZilchShaderTestErrorSettings testSettings;

  Zilch::BoundType* testConfigType = ZilchTypeId(ZilchShaderTestConfiguration);
  Zilch::BoundType* errorSettingsType = ZilchTypeId(ZilchShaderTestErrorSettings);
  Array<Zilch::Type*> mainParameters(ZeroInit, testConfigType, errorSettingsType);

  for(auto range = library->BoundTypes.Values(); !range.Empty(); range.PopFront())
  {
    Zilch::BoundType* zilchType = range.Front();

    // Find the main function with the correct signature
    Zilch::Function* mainFunction = zilchType->FindFunction("Main", mainParameters, core.VoidType, Zilch::FindMemberOptions::None);
    if(mainFunction == nullptr)
      continue;

    Zilch::ExceptionReport report;
    // Allocate the SystemValueSettings struct
    Zilch::Handle preconstructedObject = state->AllocateDefaultConstructedHeapObject(zilchType, report, Zilch::HeapFlags::NonReferenceCounted);
    // Set the ShaderSystemValueSettings class as the first parameter and call the main function
    Zilch::Call call(mainFunction, state);
    call.Set(0, &testConfig);
    call.Set(1, &testSettings);
    call.SetHandle(Zilch::Call::This, preconstructedObject);
    call.Invoke(report);

    errorSettings.mErrorOnNoMain = testSettings.mErrorOnNoMain;

    preconstructedObject.Delete();
  }
}