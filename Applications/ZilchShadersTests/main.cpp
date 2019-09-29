///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

class VisualStudioListener : public ConsoleListener
{
public:
  void Print(FilterType filterType, cstr message) override
  {
    OutputDebugStringA(message);
  }
};

void ZilchCompilerErrorCallback(Zilch::ErrorEvent* e)
{
  String msg = e->GetFormattedMessage(Zilch::MessageFormat::MsvcCpp);
  ZPrint("%s", msg.c_str());
  ZeroDebugBreak();
}

void ZilchTranslationErrorCallback(TranslationErrorEvent* e)
{
  String msg = e->mFullMessage;
  ZPrint("%s", msg.c_str());
  __debugbreak();
}

void RunTests()
{
  // Hook up a listener to print all output to the visual studio console
  VisualStudioListener visualStudioOutput;
  if(Os::IsDebuggerAttached())
    Zero::Console::Add(&visualStudioOutput);

  HWND hiddenWindow = CreateWindowA("STATIC", "", WS_POPUP | WS_DISABLED, 0, 0, mScreenWidth, mScreenHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
  ShowWindow(hiddenWindow, SW_HIDE);
  HDC drawContext = GetDC(hiddenWindow);

  ErrorReporter glslReporter;
  GlslRenderer glslRenderer(drawContext);

  RendererPackage glslPackage;
  glslPackage.mErrorReporter = &glslReporter;
  glslPackage.mRenderer = &glslRenderer;
  ZilchShaderGlslBackend* glslBackend = new ZilchShaderGlslBackend();
  // Required to test runtime arrays
  glslBackend->mTargetVersion = 440;
  glslPackage.mBackend = glslBackend;

  UnitTestPackage unitTestPackage;
  unitTestPackage.mBackends.PushBack(new ZilchSpirVDisassemblerBackend());
  unitTestPackage.mRenderPackages.PushBack(glslPackage);

  String extensionsPath = "FragmentExtensions";
  String fragmentSettingsPath = "../../Data/ZilchFragmentSettings";

  SpirVNameSettings nameSettings;
  SimpleZilchShaderIRGenerator::LoadNameSettings(nameSettings);
  ZilchShaderSpirVSettings* settings = SimpleZilchShaderIRGenerator::CreateUnitTestSettings(nameSettings);
  SimpleZilchShaderIRGenerator irGenerator(new ZilchSpirVFrontEnd(), settings);
  Zilch::EventConnect(&irGenerator, Zilch::Events::CompilationError, ZilchCompilerErrorCallback);
  Zilch::EventConnect(&irGenerator, Zero::Events::TranslationError, &ErrorReporter::OnTranslationError, &glslReporter);
  Zilch::EventConnect(&irGenerator, Zilch::Events::CompilationError, &ErrorReporter::OnCompilationError, &glslReporter);
  Zilch::EventConnect(&irGenerator, Zero::Events::ValidationError, &ErrorReporter::OnValidationError, &glslReporter);

  irGenerator.SetupDependencies(extensionsPath);

  TestDirectory(irGenerator, unitTestPackage, "IrTests", glslReporter, true);
  TestDirectory(irGenerator, unitTestPackage, "IrCompositeTests", glslReporter, true);

  // Currently requires 150 for how uniforms are passed through.
  // @JoshD: update to uniform buffers later.
  glslBackend->mTargetVersion = 150;
  TestRunning(irGenerator, unitTestPackage, "RunningIrTests", true);
  
  glslReporter.mAssert = false;
  TestDirectory(irGenerator, unitTestPackage, "IrErrorTests", glslReporter, true);

  // Run all of the unit test directories with our different translators/renderers
  //for(size_t i = 0; i < shaderLanguages.Size(); ++i)
  //{
  //  ShaderLanguageTestData& shaderLanguage = *(shaderLanguages[i]);
  //  SimpleZilchShaderGenerator& shaderGenerator = shaderLanguage.mShaderGenerator;
  //  Zilch::EventConnect(&shaderGenerator, Zilch::Events::CompilationError, ZilchCompilerErrorCallback);
  //  Zilch::EventConnect(&shaderGenerator, Zero::Events::TranslationError, ZilchTranslationErrorCallback);
  //  shaderGenerator.LoadSettings(fragmentSettingsPath);
  //  shaderGenerator.SetupDependencies(extensionsPath);
  //
  //  ZPrint("Running %s tests\n", shaderGenerator.mTranslator->GetFullLanguageString().c_str());
  //  TestRenderer(shaderGenerator, *shaderLanguage.mRenderer, *shaderLanguage.mErrorReporter);
  //}
}

int main()
{
  Zilch::ZilchSetup zilchSetup;

  Zilch::Module module;
  Zilch::ExecutableState::CallingState = module.Link();

  ShaderSettingsLibrary::InitializeInstance();
  ShaderSettingsLibrary::GetInstance().GetLibrary();
  ShaderTestLibrary::InitializeInstance();
  ShaderTestLibrary::GetInstance().GetLibrary();
  RunTests();

  ShaderTestLibrary::GetInstance().Destroy();
  ShaderSettingsLibrary::GetInstance().Destroy();
  delete Zilch::ExecutableState::CallingState;

  return 0;
}
