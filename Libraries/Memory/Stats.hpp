///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters, Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Memory.hpp"

namespace Zero
{

namespace Memory
{

//-------------------------------------------------------------------Stats
struct Stats
{
  enum StatFlags
  {
    ShowActive     = 1,
    ShowDedicated  = 2,
    ShowPeak       = 4,
    ShowBytes      = 8,
    ShowTotal      = 16,
    ShowLocal      = 32,
    ShowCount      = 64
  };

  MemCounterType Allocations;
  MemCounterType Active;
  MemCounterType BytesAllocated;
  MemCounterType BytesDedicated;
  MemCounterType PeakAllocated;

  Stats()
    : Allocations(0)
    , Active(0)
    , BytesAllocated(0)
    , BytesDedicated(0)
    , PeakAllocated(0)
  {
  }

  void Accumulate(const Stats& right)
  {
    Allocations += right.Allocations;
    Active += right.Active;
    BytesAllocated += right.BytesAllocated;
    BytesDedicated += right.BytesDedicated;
    PeakAllocated += right.PeakAllocated;
  }

#define VisitByName(name) vistor(#name, name)
  template<typename Vistor>
  void Visit(Vistor& vistor, size_t flags)
  {
    if(flags & ShowActive)
      VisitByName(Active);

    if(flags & ShowCount)
      VisitByName(Allocations);

    if(flags & ShowBytes)
      VisitByName(BytesAllocated);

    if(flags & ShowDedicated)
      VisitByName(BytesDedicated);

    if(flags & ShowPeak)
      VisitByName(PeakAllocated);
  }
#undef VisitByName
};

}//namespace Memory

}//namespace Zero
