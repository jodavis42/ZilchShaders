///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Memory.hpp"
#include "Memory/Stats.hpp"
#include "FixedContainers/InList.hpp"
#include "FixedContainers/FixedString.hpp"

namespace Zero
{

namespace Memory
{

//-------------------------------------------------------------------GraphNode
///Base Memory graph node. All allocators are derived from this class for
///runtime memory statics collection and debugging. Class provides a graph
///structure for hierarchical grouping of memory and the ability to name allocators.
class GraphNode : public LinkBase
{
public:
  UseStaticMemory();

  typedef FixedString<32> NameType;
  NameType Name;
  GraphNode* mParent;
  Stats mData;

  typedef InListBaseLink<GraphNode>::range RangeType;

  GraphNode(cstr name, GraphNode* parent);
  virtual ~GraphNode();
  virtual void CleanUp();
 
  void DeltaDedicated(MemCounterType bytes);
  void AddAllocation(MemCounterType bytes);
  void RemoveAllocation(MemCounterType bytes);
  void Compute(Stats& data);

  cstr GetName() { return Name.c_str(); }
  RangeType GetChildren() { return Children.All(); }

  InListBaseLink<GraphNode> Children;
private:
  //Can not copy memory managers.
  GraphNode(const GraphNode&);
  void operator=(const GraphNode&);
};

}//namespace Memory
}//namespace Zero
