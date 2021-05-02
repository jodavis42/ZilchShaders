///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ZilchShadersStandard.hpp"

#include "IAttributeResolver.hpp"

namespace Zero
{

//-------------------------------------------------------------------AttributeResolverSortData
class AttributeResolverSortData
{
public:
  IAttributeResolver* mResolver = nullptr;
  ZilchShaderIRType* mShaderType = nullptr;
  Zilch::SyntaxNode* mNode = nullptr;
  size_t mAttributeIndex = 0;

  static int Sort(const AttributeResolverSortData& lhs, const AttributeResolverSortData& rhs)
  {
    float lhsPriority = lhs.mResolver->GetPriority();
    float rhsPriority = rhs.mResolver->GetPriority();
    if(lhsPriority == rhsPriority)
      return 0;
    return lhsPriority < rhsPriority;
  }
};

}//namespace Zero