///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "PointerRange.hpp"

namespace Zero
{

//-------------------------------------------------------------------FixedArray
template<typename type, size_t maxSize>
class FixedArray
{
public:
  typedef type value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef FixedArray<type, maxSize> this_type;
  typedef ConstPointerRange<type> Range;

  explicit FixedArray()
    : mSize(0)
  {}

  explicit FixedArray(size_type size)
    : mSize(size)
  {}

  FixedArray(pointer data, size_type size)
    : mSize(size)
  {
    if(mSize > maxSize) mSize = maxSize;
    UninitializedCopy(mData, data, mSize, true_type());
  }

  Range All() { return range(mData, mSize); }
  bool Empty()const { return mSize == 0; }
  const_pointer Data() const { return mData; }
  size_type Size() const { return mSize; }
  size_type capacity() const { return maxSize; }

  reference Front()
  {
    ErrorIf(mSize == 0, "Empty array, no front element.");
    return mData[0];
  }

  const_reference Front() const
  {
    ErrorIf(mSize == 0, "Empty array, no front element.");
    return mData[0];
  }

  reference Back()
  {
    ErrorIf(mSize == 0, "Empty array, no back element.");
    return mData[mSize - 1];
  }

  const_reference Back() const
  {
    ErrorIf(mSize == 0, "Empty array, no back element.");
    return mData[mSize - 1];
  }

  void PushBack(type& element)
  {
    ErrorIf(mSize>=maxSize, "Array at max size");
    mData[mSize] = element;
    ++mSize;
  }

  type& PushBack()
  {
    ErrorIf(mSize>=maxSize, "Array at max size");
    ++mSize;
    return *(mData+(mSize-1));
  }

  //Removes the last element in the array.
  void PopBack()
  {
    ErrorIf(mSize == 0,"Empty array, can not pop back element.");
    --mSize;
  }

  void EraseIndex(uint index)
  {
    ErrorIf(index>mSize, "Index out of bounds.");
    //Shift over values
    uint lastValid = mSize-1;
    for(uint i=index;index<lastValid;++i)
      mData[i] = mData[i+1];
    //decrement size
    --mSize;
  }

  //simple erase value
  void EraseValue(type& value)
  {
    for(uint i=0;i<mSize;++i)
    {
      if(mData[i] == value)
      {
        //value found remove it
        EraseIndex(i);
        return;
      }
    }
  }

protected:
  type mData[maxSize];
  size_type mSize;
};

}//namespace Zero
