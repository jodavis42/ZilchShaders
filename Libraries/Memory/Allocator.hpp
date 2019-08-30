///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Memory.hpp"
#include "Stats.hpp"

namespace Zero
{

namespace Memory
{

//-------------------------------------------------------------------Allocator
///Base Memory graph node. All allocators are derived from this class for
///runtime memory statics collection and debugging. Class provides a graph
///structure for hierarchical grouping of memory and the ability to name allocators.
class Allocator
{
public:
  Allocator();
  virtual ~Allocator();

  void DeltaDedicated(MemCounterType bytes);
  void AddAllocation(MemCounterType bytes);
  void RemoveAllocation(MemCounterType bytes);

  Stats mData;

private:
};

}//namespace Memory

}//namespace Zero
