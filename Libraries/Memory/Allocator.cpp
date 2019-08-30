///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "Allocator.hpp"

namespace Zero
{

namespace Memory
{

//-------------------------------------------------------------------Allocator
Allocator::Allocator()
{
}

Allocator::~Allocator()
{
}

void Allocator::DeltaDedicated(MemCounterType bytes)
{
  mData.BytesDedicated += bytes;
}

void Allocator::AddAllocation(MemCounterType bytes)
{
  ++mData.Active;
  ++mData.Allocations;
  mData.BytesAllocated += bytes;
  if(mData.BytesAllocated > mData.PeakAllocated)
    mData.PeakAllocated = mData.BytesAllocated;
}

void Allocator::RemoveAllocation(MemCounterType bytes)
{
  --mData.Active;
  mData.BytesAllocated -= bytes;
}

}//namespace Memory

}//namespace Zero
