///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "Heap.hpp"

namespace Zero
{

namespace Memory
{

//-------------------------------------------------------------------Heap
Heap::Heap(cstr name, GraphNode* parent)
  : GraphNode(name, parent)
{
}

MemPtr Heap::Allocate(size_t numberOfBytes)
{
  AddAllocation(numberOfBytes);
  MemPtr mem = zAllocate(numberOfBytes);
  return mem;
}

void Heap::Deallocate(MemPtr ptr, size_t numberOfBytes)
{
  RemoveAllocation(numberOfBytes);
  zDeallocate(ptr);
}

}//namespace Memory

}//namespace Zero
