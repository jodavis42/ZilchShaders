///////////////////////////////////////////////////////////////////////////////
/// Authors: Chris Peters
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "FixedArray.hpp"

namespace Zero
{


//-------------------------------------------------------------------FixedString
template<size_t maxSize>
class FixedString : public FixedArray<char, maxSize>
{
public:
  typedef char CharType;
  typedef FixedArray<CharType, maxSize> base_type;
  typedef FixedString<maxSize> this_type;
  typedef typename base_type::const_pointer const_pointer;
  typedef typename base_type::size_type size_type;
  
  typedef PointerRange<CharType> Range;
  Range All()
  { 
    return Range(this->mData, this->mData + this->mSize);
  }

  FixedString()
    : base_type(0)
  {
    memset(this->mData, 0, maxSize);
  }

  explicit FixedString(const_pointer cstring)
  {
    Assign(cstring, strlen(cstring));
  }

  explicit FixedString(Range r)
  {
    Assign(r.Data(), r.SizeInBytes());
  }

  template<size_t otherSize>
  explicit FixedString(const FixedString<otherSize>& fstring)
  {
    Assign(fstring.Data(), fstring.Size());
  }

  void operator=(const_pointer cstring)
  {
    Assign(cstring, strlen(cstring));
  }

  void operator=(Range r)
  {
    Assign(r.Data(), r.SizeInBytes());
  }

  void Assign(const_pointer cstring, size_type size)
  {
    memset(this->mData, 0, maxSize);

    if (size > maxSize - 1)
    {
      Error("String is not large enough for range.");
      size = maxSize - 1;
    }
    
    this->mSize = size;
    //need room for null terminator
    if(this->mSize > (maxSize - 1))
      this->mSize = maxSize - 1;

    memcpy(this->mData, cstring, this->mSize);
    this->mData[this->mSize] = '\0';
  }

  template<size_t otherSize>
  friend inline bool operator==(const this_type& left,
                                const FixedString<otherSize>& right)
  {
    return strcmp(left.Data(), right.Data()) == 0;
  }

  template<size_t otherSize>
  friend inline bool operator!=(const this_type& left,
    const FixedString<otherSize>& right)
  {
    return !(left == right);
  }

  template<size_t otherSize>
  friend inline bool operator<(const this_type& left, 
                               const FixedString<otherSize>& right)
  {
    return strcmp(left.Data(), right.Data()) < 0;
  }

  const_pointer c_str()const{return this->mData;}
};

template<size_t s>
inline bool operator==(const FixedString<s>& left, cstr right)
{
  return strcmp(left.Data(), right) == 0;
}

template<size_t s>
inline bool operator!=(const FixedString<s>& left, cstr right)
{
  return strcmp(left.Data(), right) != 0;
}

//template<size_t s>
//inline bool operator==(const FixedString<s>& left, const FixedString<s>::Range& right)
//{
//  return strcmp(left.Data(), right.Data()) == 0;
//}
//
//template<size_t s>
//inline bool operator==(const FixedString<s>::Range& left, const FixedString<s>& right)
//{
//  return strcmp(left.Data(), right.Data()) == 0;
//}

}//namespace Zero
