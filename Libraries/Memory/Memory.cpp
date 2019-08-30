///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters, Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "Memory.hpp"

#include <new>
namespace Zero
{

namespace Memory
{

void* zAllocate(size_t numberOfBytes)
{
#ifdef UseMemoryDebugger
  return DebugAllocate(numberOfBytes, AllocationType_Direct, 4);
#elif UseMemoryTracker
  return DebugAllocate(numberOfBytes, 4);
#else
  return malloc(numberOfBytes);
#endif
}

void zDeallocate(void* ptr)
{
#ifdef UseMemoryDebugger
  DebugDeallocate(ptr, AllocationType_Direct);
#elif UseMemoryTracker
  return DebugDeallocate(ptr);
#else
  return free(ptr);
#endif
}

MemPtr zStaticAllocate(size_t size)
{
  static const uint cStaticMemoryBufferSize = 5000;
  static byte StaticMemoryGraphBuffer[cStaticMemoryBufferSize];
  static byte* BufferLocation = StaticMemoryGraphBuffer;

  //Static Memory graph nodes and other static objects
  //are allocated from a fixed size buffer this allows them to have controlled 
  //or optional initialization and prevents them from showing up in leaks
  ErrorIf(BufferLocation + size >= StaticMemoryGraphBuffer + cStaticMemoryBufferSize,
    "Allocated too many memory graph objects. Increase cStaticMemoryBufferSize.");
  byte* current = BufferLocation;
  BufferLocation+=size;
  //DebugPrint("Max Static Memory %d\n", uint(BufferLocation - StaticMemoryGraphBuffer));
  return current;
}

void StandardMemory::MemCopy(void* dest, void* source, size_t numberOfBytes)
{
  memcpy(dest, source, numberOfBytes);
}

void StandardMemory::MemMove(void* dest, void* source, size_t numberOfBytes)
{
  memmove(dest, source, numberOfBytes);
}

}//namespace Memory

}//namespace Zero
