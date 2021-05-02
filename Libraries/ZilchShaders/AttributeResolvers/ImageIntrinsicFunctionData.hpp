///////////////////////////////////////////////////////////////////////////////
/// Authors: Joshua Davis
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ZilchShadersStandard.hpp"
#include "Enums/ImageEnums.hpp"

namespace Zero
{

//-------------------------------------------------------------------ImageIntrinsicFunctionData
/// Specifies an intrinsic function for an image. Image intrinsics are more complicated as they may take a mask
/// that controls what extra parameters exist. This mask isn't always at a consistent location like the end of the function either,
/// so the location was added for user control. The location specifies what function argument this should be placed before,
/// so if location is 2 and there are 3 arguments then it's: [arg0, arg1, operandsMask, arg2].
/// If no mask and location are specified, then no mask is written (not all intrinsics specify a mask either).
/// A Image intrinsic function expects the first parameter to either be an image or a sampled image.
class ImageIntrinsicFunctionData
{
public:
  bool Parse(ZilchSpirVFrontEnd* translator, ShaderIRAttribute& attribute);

  String mOpName;
  OpType mOpType;
  ImageOperands::Enum mOperands = ImageOperands::None;
  u32 mOperandsLocation = -1;
};

}//namespace Zero