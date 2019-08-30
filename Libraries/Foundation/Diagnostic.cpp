///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters, Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "Diagnostic.hpp"

namespace Zero
{

const int cDebugBufferLength = 1024;

//-------------------------------------------------------------------ErrorSignaler
ErrorSignaler::ErrorHandler ErrorSignaler::mActiveErrorHandler = EmptyErrorHandler;

ErrorSignaler::ErrorSignaler()
{
  mActiveErrorHandler = EmptyErrorHandler;
}

void ErrorSignaler::SetErrorHandler(ErrorHandler newHandler)
{
  mActiveErrorHandler = newHandler;
}

ErrorSignaler::ErrorHandler ErrorSignaler::GetErrorHandler()
{
  return mActiveErrorHandler;
}

bool ErrorSignaler::SignalError(SignalErrorType signalType, cstr exp,
                               cstr file, int line, bool& ignore, 
                               cstr msgFormat, ...)
{
  if(ignore)
    return false;

  ErrorData errorData;
  errorData.Line = line;
  errorData.File = file;
  errorData.Expression = exp;
  errorData.ErrorType = signalType;
  errorData.Message = nullptr;
  errorData.IgnoreFutureAssert = false;

  if(msgFormat != nullptr)
  {
    va_list args;
    va_start(args, msgFormat);
    //Get the number of characters needed for message
    int bufferSize;
    ZeroVSPrintfCount(msgFormat, args, 1, bufferSize);

    char* messageBuffer = (char*)alloca((bufferSize+1)*sizeof(char));
    ZeroVSPrintf(messageBuffer, bufferSize+1, msgFormat, args);
    va_end(args);
    errorData.Message = messageBuffer;
  }

  bool result = (*mActiveErrorHandler)(errorData);
  ignore = errorData.IgnoreFutureAssert;
  return result;
}

bool EmptyErrorHandler(ErrorSignaler::ErrorData& errorData)
{
  return true;
}

}//namespace Zero
