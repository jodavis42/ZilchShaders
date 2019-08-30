///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Memory.hpp"

namespace Zero
{

namespace Memory
{

//-------------------------------------------------------------------TypedAllocator
template<typename NodeType>
class TypedAllocator : public Memory::StandardMemory
{
  typedef TypedAllocator<NodeType> this_type;

public:
  TypedAllocator()
    :mNode(Memory::GetGlobalHeap())
  {
  }

  TypedAllocator(cstr name)
    :mNode(Memory::GetNamedHeap(name))
  {
  }

  TypedAllocator(NodeType* manager)
    :mNode(manager)
  {
  }

  MemPtr Allocate(size_t numberOfBytes){return mNode->Allocate(numberOfBytes); };
  void Deallocate(MemPtr ptr, size_t numberOfBytes){mNode->Deallocate(ptr, numberOfBytes);}
  NodeType* mNode;
};

//-------------------------------------------------------------------MemsetZeroTypedAllocator
// This allocator specifically works with 
template<typename NodeType>
class MemsetZeroTypedAllocator : public TypedAllocator<NodeType>
{
public:
  MemsetZeroTypedAllocator()
    :mNode(Memory::GetGlobalHeap())
  {
  }

  MemsetZeroTypedAllocator(cstr name)
    :mNode(Memory::GetNamedHeap(name))
  {
  }

  MemsetZeroTypedAllocator(NodeType* manager)
    :mNode(manager)
  {
  }

  MemPtr Allocate(size_t numberOfBytes)
  {
    if(mNode == nullptr)
      mNode = Memory::GetGlobalHeap();
    return mNode->Allocate(numberOfBytes);
  }

  void Deallocate(MemPtr ptr, size_t numberOfBytes)
  {
    if(mNode == nullptr)
      mNode = Memory::GetGlobalHeap();
    mNode->Deallocate(ptr, numberOfBytes);
  }

  NodeType* mNode;
};

} // namespace Memory

} // namespace Zero
