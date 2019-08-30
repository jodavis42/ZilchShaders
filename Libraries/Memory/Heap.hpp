///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Memory.hpp"
#include "Allocator.hpp"
#include "GraphNode.hpp"
#include "TypedAllocator.hpp"

namespace Zero
{

namespace Memory
{

//-------------------------------------------------------------------Heap
///Heap allocator. The heap allocator allocates memory directly from the 
///system heap using malloc and free.
class Heap : public GraphNode
{
public:
  Heap(cstr name, GraphNode* parent);
  MemPtr Allocate(size_t numberOfBytes);
  void Deallocate(MemPtr ptr, size_t numberOfBytes);
};

template <typename type>
type* HeapAllocate(Heap* heap)
{
  MemPtr memory = heap->Allocate(sizeof(type));
  type* object = new(memory) type();
  return object;
}

template <typename type, typename ConstructionType>
type* HeapAllocate(Heap* heap, const ConstructionType& constructionData)
{
  MemPtr memory = heap->Allocate(sizeof(type));
  type* object = new(memory) type(constructionData);
  return object;
}

template <typename type>
void HeapDeallocate(Heap* heap, type* instance)
{
  instance->~type();
  heap->Deallocate(instance,sizeof(type));
}

}//namespace Memory

#define UseStaticHeap() \
  static void* operator new(size_t size){ return Memory::GetStaticHeap()->Allocate(size); } \
  static void operator delete(void* pMem, size_t size){return Memory::GetStaticHeap()->Deallocate(pMem, size);}

typedef Memory::TypedAllocator<Memory::Heap> HeapAllocator;

//Override default
typedef Memory::TypedAllocator<Memory::Heap> DefaultAllocator;
typedef Memory::MemsetZeroTypedAllocator<Memory::Heap> MemsetZeroDefaultAllocator;

}//namespace Zero
