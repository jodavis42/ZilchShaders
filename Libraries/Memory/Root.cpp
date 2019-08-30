///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

#include "Root.hpp"
#include "Heap.hpp"

namespace Zero
{

namespace Memory
{

//-------------------------------------------------------------------Root
Root* Root::RootGraph = nullptr;
Heap* Root::GloblHeap = nullptr;
Heap* Root::StaticHeap = nullptr;

void Shutdown()
{
  GetRoot()->CleanUp();
  GetRoot()->Shutdown();
}

void Root::Shutdown()
{
  //Only delete the root
  //the root graph node will delete all child graph
  //nodes and clean up memory.
  if(RootGraph != nullptr)
  {
    delete RootGraph;
    RootGraph = nullptr;
  }
}

void Root::Initialize()
{
  if(RootGraph == nullptr)
  {
    RootGraph = new Root("Root", nullptr);
    StaticHeap = new Heap("Static", RootGraph);
    GloblHeap = new Heap("Global", RootGraph);
  }
}

Root* GetRoot()
{
  Root::Initialize();
  return Root::RootGraph;
}

Heap* GetGlobalHeap()
{
  Root::Initialize();
  return Root::GloblHeap;
}

Heap* GetStaticHeap()
{
  Root::Initialize();
  return Root::StaticHeap;
}

Heap* GetNamedHeap(cstr name)
{
  Root::Initialize();

  // Implement me
  __debugbreak();

  return nullptr;
}

}//namespace Memory

}//namespace Zero
