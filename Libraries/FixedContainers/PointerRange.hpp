///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Zero
{

//-------------------------------------------------------------------ConstPointerRange
// Constant Pointer Range. Forms a range between two pointers.
template<typename type>
struct ConstPointerRange
{
  typedef const type* iterator;

  //Construct a range with two pointers.
  ConstPointerRange(iterator pbegin, iterator pend)
    : begin(pbegin), end(pend)
  {
  }

  //Construct a range with a pointer and a size.
  ConstPointerRange(iterator pbegin, size_t size)
    : begin(pbegin), end(pbegin + size)
  {
  }

  const type& Front() { return *begin; }
  void PopFront()
  {
    ErrorIf(Empty(), "Popped empty range.");
    ++begin;
  }

  bool Empty() { return begin == end; }
  size_t Length() { return end - begin; }

  ConstPointerRange& All() { return *this; }
  const ConstPointerRange& All() const { return *this; }

  iterator begin;
  iterator end;
};

//-------------------------------------------------------------------PointerRange
// Pointer Range. Forms a range between two pointers.
template<typename type>
struct PointerRange
{
  typedef type* iterator;

  //Construct a range with two pointers.
  PointerRange(iterator pbegin, iterator pend)
    : begin(pbegin), end(pend)
  {
  }

  //Construct a range with a pointer and a size.
  PointerRange(iterator pbegin, size_t size)
    : begin(pbegin), end(pbegin + size)
  {
  }

  type& Front() { return *begin; }
  void PopFront()
  {
    ErrorIf(Empty(), "Popped empty range.");
    ++begin;
  }

  bool Empty() { return begin == end; }
  size_t Length() { return end - begin; }
  iterator begin;
  iterator end;
};

}//namespace Zero
