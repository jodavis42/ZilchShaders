///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "GraphNode.hpp"

namespace Zero
{

namespace Memory
{

//-------------------------------------------------------------------GraphNode
GraphNode::GraphNode(cstr name, GraphNode* parent)
  : Name(name), mParent(parent)
{
  if(parent != nullptr)
    parent->Children.PushBack(this);
}

GraphNode::~GraphNode()
{
  DeleteObjectsIn(Children);
}

void GraphNode::CleanUp()
{
  RangeType sub = Children.All();
  while(!sub.Empty())
  {
    sub.Front().CleanUp();
    sub.PopFront();
  }
}

void GraphNode::DeltaDedicated(MemCounterType bytes)
{
  mData.BytesDedicated += bytes;
}

void GraphNode::AddAllocation(MemCounterType bytes)
{
  ++mData.Active;
  ++mData.Allocations;
  mData.BytesAllocated += bytes;
  if(mData.BytesAllocated > mData.PeakAllocated)
    mData.PeakAllocated = mData.BytesAllocated;
}

void GraphNode::RemoveAllocation(MemCounterType bytes)
{
  --mData.Active;
  mData.BytesAllocated -= bytes;
}

void GraphNode::Compute(Stats& data)
{
  data.Accumulate(mData);
  RangeType sub = Children.All();
  while(!sub.Empty())
  {
    sub.Front().Compute(data);
    sub.PopFront();
  }
}

}//namespace Memory

}//namespace Zero
