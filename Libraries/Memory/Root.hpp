///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Memory/GraphNode.hpp"

namespace Zero
{

namespace Memory
{

class Heap;

//-------------------------------------------------------------------Root
class Root : public GraphNode
{
public:
  Root(cstr name, GraphNode* parent)
    :GraphNode(name, parent)
  {
  }

  static Root* RootGraph;
  static Heap* GloblHeap;
  static Heap* StaticHeap;

  static void Initialize();
  static void Shutdown();
  static void PrintAll();
};

Heap* GetGlobalHeap();
Heap* GetNamedHeap(cstr name);
Root* GetRoot();
Heap* GetStaticHeap();
void Shutdown();

}//namespace Memory

}//namespace Zero
