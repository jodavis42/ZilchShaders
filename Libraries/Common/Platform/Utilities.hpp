///////////////////////////////////////////////////////////////////////////////
///
/// \file Utilities.hpp
/// Declaration of the Utilities class.
/// 
/// Authors: Trevor Sundberg, Chris Peters
/// Copyright 2011, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Zero
{
/// System Memory Information
struct MemoryInfo
{
  size_t Reserve;
  size_t Commit;
  size_t Free;
};

namespace Os
{

// Sleep the current thread for ms milliseconds.
void Sleep(uint ms);

// Set the Timer Frequency (How often the OS checks threads for sleep, etc)
void SetTimerFrequency(uint ms);

// Get the user name for the current profile
String UserName();

// Get the computer name
String ComputerName();

// Get computer Mac Address of adapter 0
u64 GetMacAddress();

// Check if a debugger is attached
bool IsDebuggerAttached();

// Output a message to any attached debuggers
void DebuggerOutput(const char* message);

// Debug break (only if a debugger is attached)
void DebugBreak();

// Attempts to enable memory leak checking (break on 
void EnableMemoryLeakChecking(int breakOnAllocation = -1);

// When a diagnostic error occurs, this is the default response
bool ErrorProcessHandler(ErrorSignaler::ErrorData& errorData);

// Verb used to open file
DeclareEnum4(Verb, Default, Open, Edit, Run);

// Open the file using the appropriate Os application or
// launch an external application.
void SystemOpenFile(cstr file, uint verb=Verb::Default, cstr parameters = nullptr, cstr workingDirectory = nullptr);
bool SystemOpenFile(Status& status, cstr file, uint verb=Verb::Default, cstr parameters = nullptr, cstr workingDirectory = nullptr);

// Open the network file (including urls) using the appropriate
// Os application or launch an external application
void SystemOpenNetworkFile(cstr file, uint verb = Verb::Default, cstr parameters = nullptr, cstr workingDirectory = nullptr);
bool SystemOpenNetworkFile(Status& status, cstr file, uint verb = Verb::Default, cstr parameters = nullptr, cstr workingDirectory = nullptr);

// Get the memory status of the Os.
void GetMemoryStatus(MemoryInfo& memoryInfo);

// Get an Environmental variable
String GetEnvironmentalVariable(StringParam variable);

// Get a string describing the current operating system version.
String GetVersionString();

}

// Generate a 64 bit unique Id. Uses system timer and mac
// address to generate the id.
u64 GenerateUniqueId64();

// Waits for expression to evaluate to true, checking approximately every pollPeriod (in milliseconds)
#define WaitUntil(expression, pollPeriod) \
do { while(!(expression)) { Os::Sleep(pollPeriod); } } while(gConditionalFalseConstant)

}//namespace Zero
