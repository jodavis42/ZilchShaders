///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Davis
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

void LoadSettingsOrDefault(ZilchShaderSpirVSettings& settings, StringParam defFilePath);
void LoadDirectorySettingsOrDefault(ZilchShaderSpirVSettings& settings, StringParam directoryPath);
void LoadFragmentCodeDirectory(SimpleZilchShaderIRGenerator& shaderGenerator, StringParam directory);

// Simple function to display a diff error in notepad++ (ideally use a better text editor or something later)
void DisplayError(StringParam filePath, StringParam lineNumber, StringParam errMsg);

void FileToStream(File& file, TextStreamBuffer& stream);
void RunProcess(StringParam applicationPath, StringParam args, String* stdOutResult, String* stdErrResult);
