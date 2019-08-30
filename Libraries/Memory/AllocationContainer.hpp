///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters, Andrew Colean
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Zero
{

namespace Memory
{

//-------------------------------------------------------------------AllocationContainer
/// Base class for containers that use allocators.
template<typename AllocatorType>
class AllocationContainer
{
public:
  typedef AllocatorType allocator_type;
  allocator_type& GetAllocator() { return mAllocator; }
  void SetAllocator(const allocator_type& allocator) { mAllocator = allocator; }
protected:
  allocator_type mAllocator;
};

} // namespace Memory

} // namespace Zero
