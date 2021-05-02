///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ZilchShadersStandard.hpp"

namespace Zero
{

//-------------------------------------------------------------------IAttributeResolver
/// Virtual class to handle the interface for resolving certain attributes, in particular intrinsic attributes.
class IAttributeResolver
{
public:
  /// Some base priorities to use when sorting attributes.
  enum class BasePriorities
  {
    None = 0, 
    Image = 5,
    SampledImage = 6
  };

  /// Some attributes rely on an ordering to work correctly (e.g. sampled image needs image to be processed first).
  // This is used to order attribute resolve. Note: This is only currently applied to class attributes, not function.
  virtual float GetPriority() const
  {
    return static_cast<float>(BasePriorities::None);
  }

  virtual void Resolve(ZilchSpirVFrontEnd* translator, Zilch::SyntaxNode* node, ZilchShaderIRType* shaderType, ShaderIRAttributeList& attributes, ShaderIRAttribute& attribute) abstract;
};

}//namespace Zero