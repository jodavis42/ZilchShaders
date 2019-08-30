///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters, Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Foundation/Standard.hpp"

namespace Zero
{

namespace Memory
{

typedef size_t MemCounterType;
typedef void* MemPtr;

MemPtr zAllocate(size_t numberOfBytes);
void zDeallocate(MemPtr);
MemPtr zStaticAllocate(size_t size);

#define UseStaticMemory()                                                \
  static void* operator new(size_t size){return zStaticAllocate(size);}  \
  static void operator delete(void* /*pMem*/, size_t /*size*/){}

#define OverloadedNew()                                             \
  static void* operator new(size_t size);                           \
  static void  operator delete(void* pMem, size_t size);            \
  static void* operator new (size_t size, void* ptr){return ptr;};  \
  static void  operator delete(void* mem, void* ptr){};

#define ImplementOverloadedNewWithAllocator(ClassName, AllocatorObj)                                 \
  void* ClassName::operator new(size_t size) { return AllocatorObj->Allocate(size); };               \
  void  ClassName::operator delete(void* pMem, size_t size) { AllocatorObj->Deallocate(pMem, size); }

//-------------------------------------------------------------------StandardMemory
class StandardMemory
{
public:
  static void MemCopy(void* dest, void* source, size_t numberOfBytes);
  static void MemMove(void* dest, void* source, size_t numberOfBytes);
};

}//namespace Memory

}//namespace Zero

