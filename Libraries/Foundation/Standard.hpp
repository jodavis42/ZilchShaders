///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters
///////////////////////////////////////////////////////////////////////////////
#pragma once

#define AutoDeclare(varName, expression) \
    auto varName = expression

#define AutoDeclareReference(varName, expression) \
    auto& varName = expression

typedef std::nullptr_t NullPointerType;
namespace Zero
{
  typedef std::nullptr_t NullPointerType;
}

