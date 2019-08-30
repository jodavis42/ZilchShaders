/**************************************************************\
* Author: Trevor Sundberg
* Copyright 2016, DigiPen Institute of Technology
\**************************************************************/

#pragma once
#ifndef ZILCH_ARRAY_HPP
#define ZILCH_ARRAY_HPP

namespace Zilch
{
  // Instantiates an array template when requested
  BoundType* InstantiateArray
  (
    LibraryBuilder& builder,
    StringParam baseName,
    StringParam fullyQualifiedName,
    const Array<Constant>& templateTypes,
    const void* userData
  );
  
  // For every instantiated array, it may want to look up information about what it Contains
  class ArrayUserData
  {
  public:
    ArrayUserData();

    Type* ContainedType;
    BoundType* RangeType;
    BoundType* SelfType;
  };

  // This is the base definition of our array class
  // It is not technically the leaf level class, but it is binary compatible with the Zilch Array template
  // We add no members or virtuals in the derived class, and static assert that the sizes are the same
  template <typename T>
  class ZeroSharedTemplate ArrayClass
  {
  public:
    // Constructor
    ArrayClass() :
      ModifyId(0)
    {
    }

    // Invalidates all active ranges via incrementing a modification id
    void Modified()
    {
      ++this->ModifyId;
    }

    // Our array is actually just an array of Any types
    // but for arrays of primitive/built in types, it will be optimized
    Array<T> NativeArray;

    // A special counter that we use to denote whenever the container has been modified
    Integer ModifyId;
  };

  static_assert(offsetof(ArrayClass<int>, NativeArray) == 0,
    "The native array must be at offset 0 so that we can binary reinterpret a Zilch ArrayClass as just a normal native Array (unsafe, but performant)");

  // These are all the specializations that are optimized to store exactly that data type
  // All values that are unknown will be stored as the 'Any' type
  #define ZilchDeclareDefineArray(ElementType, Linkage)           \
    ZilchDeclareCustomType(ArrayClass<ElementType>, ZZ::Core::GetInstance().GetBuilder()->InstantiateTemplate("Array", ZilchConstants(ZilchTypeId(ElementType)), LibraryArray(ZeroInit, Core::GetInstance().GetBuilder()->BuiltLibrary)).Type, Linkage);

  #define ZilchDeclareDefineValueArray(ElementType, Linkage)      \
    ZilchDeclareDefineArray(ElementType, Linkage)                 \
    typedef ArrayClass<ElementType> Array##ElementType;

  #define ZilchDeclareDefineHandleArray(ElementType, Linkage)     \
    ZilchDeclareDefineArray(HandleOf<ElementType>, Linkage)       \
    typedef ArrayClass<HandleOf<ElementType>> Array##ElementType;

  // Pre-existing useful declarations
  typedef HandleOf<String> HandleOfString;
  ZilchDeclareDefineValueArray (Handle        , ZeroShared);
  ZilchDeclareDefineValueArray (Delegate      , ZeroShared);
  ZilchDeclareDefineValueArray (Boolean       , ZeroShared);
  ZilchDeclareDefineValueArray (Boolean2      , ZeroShared);
  ZilchDeclareDefineValueArray (Boolean3      , ZeroShared);
  ZilchDeclareDefineValueArray (Boolean4      , ZeroShared);
  ZilchDeclareDefineValueArray (Byte          , ZeroShared);
  ZilchDeclareDefineValueArray (Integer       , ZeroShared);
  ZilchDeclareDefineValueArray (Integer2      , ZeroShared);
  ZilchDeclareDefineValueArray (Integer3      , ZeroShared);
  ZilchDeclareDefineValueArray (Integer4      , ZeroShared);
  ZilchDeclareDefineValueArray (Real          , ZeroShared);
  ZilchDeclareDefineValueArray (Real2         , ZeroShared);
  ZilchDeclareDefineValueArray (Real3         , ZeroShared);
  ZilchDeclareDefineValueArray (Real4         , ZeroShared);
  ZilchDeclareDefineValueArray (Quaternion    , ZeroShared);
  ZilchDeclareDefineValueArray (DoubleInteger , ZeroShared);
  ZilchDeclareDefineValueArray (DoubleReal    , ZeroShared);
  ZilchDeclareDefineValueArray (Any           , ZeroShared);
  ZilchDeclareDefineHandleArray(String        , ZeroShared);
}

#endif
