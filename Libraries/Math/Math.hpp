///////////////////////////////////////////////////////////////////////////////
/// Authors: Benjamin Strukus
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Math/Reals.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"
#include "Math/Matrix2.hpp"
#include "Math/Matrix3.hpp"
#include "Math/Matrix4.hpp"
#include "Math/Quaternion.hpp"
#include "Math/EulerAngles.hpp"
#include "Math/IntVector2.hpp"
#include "Math/IntVector3.hpp"
#include "Math/IntVector4.hpp"

namespace Math
{

///Creates a skew symmetric matrix from the given 3D vector. Multiplying a 
///vector by this matrix is equivalent to the cross product using the input 
///vector.
Matrix3 SkewSymmetric(Vec3Param vec3);

///Converts a quaternion to an axis-angle pair (in radians). Axis is stored in 
///the Vector4's xyz and the angle is stored in the w.
Vector4 ToAxisAngle(QuatParam quaternion);
void ToAxisAngle(QuatParam quaternion, Vec4Ptr axisAngle);

///Converts a quaternion to an axis-angle pair (in radians).
void ToAxisAngle(QuatParam quaternion, Vec3Ptr axis, real* radians);

///Convert a 3x3 matrix to a set of Euler angles (in radians). The desired order
///of the rotations is expected to be in the given Euler angle structure.
EulerAngles ToEulerAngles(Mat3Param matrix, 
                                     EulerOrders::Enum order = EulerOrders::XYZs);
void ToEulerAngles(Mat3Param matrix, EulerAnglesPtr eulerAngles);

///Convert a 4x4 matrix to a set of Euler angles in radians. The desired order
///of the rotations is expected to be in the given Euler angle structure.
EulerAngles ToEulerAngles(Mat4Param matrix,
                                     EulerOrders::Enum order = EulerOrders::XYZs);
void ToEulerAngles(Mat4Param matrix, EulerAnglesPtr eulerAngles);

///Convert a quaternion to a set of Euler angles (in radians). The desired order
///of the rotations is expected to be in the given Euler angle structure.
EulerAngles ToEulerAngles(QuatParam quaternion, 
                                     EulerOrders::Enum order = EulerOrders::XYZs);
void ToEulerAngles(QuatParam quaternion, EulerAnglesPtr eulerAngles);

/// Converts from Vector3 to Vector2, removing the z component of the Vector3.
Vector2 ToVector2(Vec3Param v3);

/// Converts from Vector2 to Vector3, adding the given z component.
Vector3 ToVector3(Vec2Param v, real z = real(0.0));

/// Converts from Vector4 to Vector3, removing the w component.
Vector3 ToVector3(Vec4Param v);

/// Converts from Vector3 to Vector4, adding the given w component.
inline Vec4 ToVector4(Vec3Param v, real w = real(0.0)){return Vec4(v.x, v.y, v.z, w);}

// Convert from a IntVec2 to a Vec2
inline Vec2 ToVec2(IntVec2 v){return Vec2(real(v.x), real(v.y));}

// Convert from a Vec2 to a IntVec2 standard float to int conversion
inline IntVec2 ToIntVec2(Vec2Param vec2){return IntVec2(int(vec2.x), int(vec2.y));}
inline IntVec2 ToIntVec2(Vec3Param vec3){return IntVec2(int(vec3.x), int(vec3.y));}

///Converts an axis-angle pair to a 3x3 (in radians). Axis is stored in the
///Vector4's xyz and the angle is stored in the w. Axis is assumed to be 
///normalized.
Matrix3 ToMatrix3(Vec4Param axisAngle);
void ToMatrix3(Vec4Param axisAngle, Mat3Ptr matrix);

///Converts an axis-angle pair to a 3x3 matrix (in radians). Axis is assumed to
///be normalized.
Matrix3 ToMatrix3(Vec3Param axis, real radians);
void ToMatrix3(Vec3Param axis, real radians, Mat3Ptr matrix);

///Convert a set of Euler angles to a 3x3 matrix (in radians).
Matrix3 ToMatrix3(EulerAnglesParam eulerAngles);
void ToMatrix3(EulerAnglesParam eulerAngles, Mat3Ptr matrix);
///Convert a set of Euler angles to a 3x3 matrix (in radians).
Matrix3 ToMatrix3(real xRadians, real yRadians, real zRadians);

///Convert a 3x3 matrix to a 2x2 matrix. Simply copies the 3x3 matrix's upper 
///2x2 matrix (rotation & scale) to the 2x2 matrix.
Matrix2 ToMatrix2(Mat3Param matrix3);
void ToMatrix2(Mat3Param matrix3, Mat2Ptr matrix2);

///Convert a 4x4 matrix to a 3x3 matrix. Simply copies the 4x4 matrix's upper 
///3x3 matrix (rotation & scale) to the 3x3 matrix.
Matrix3 ToMatrix3(Mat4Param matrix4);
void ToMatrix3(Mat4Param matrix4, Mat3Ptr matrix3);

///Converts a quaternion to a 3x3 rotation matrix (in radians).
Matrix3 ToMatrix3(QuatParam quaternion);
void ToMatrix3(QuatParam quaternion, Mat3Ptr matrix);

Matrix3 ToMatrix3(Vec3Param facing);
Matrix3 ToMatrix3(Vec3Param facing, Vec3Param up);
Matrix3 ToMatrix3(Vec3Param facing, Vec3Param up, Vec3Param right);

///Convert a set of Euler angles to a 4x4 matrix (in radians).
Matrix4 ToMatrix4(EulerAnglesParam eulerAngles);
void ToMatrix4(EulerAnglesParam eulerAngles, Mat4Ptr matrix);

///Convert a 3x3 matrix to a 4x4 matrix. Simply copies the 3x3 matrix's values
///into the rotational part of the 4x4 matrix.
Matrix4 ToMatrix4(Mat3Param matrix3);
void ToMatrix4(Mat3Param matrix3, Mat4Ptr matrix4);

///Converts a quaternion to a 4x4 rotation matrix (in radians).
Matrix4 ToMatrix4(QuatParam quaternion);
void ToMatrix4(QuatParam quaternion, Mat4Ptr matrix);

///Converts an axis-angle pair to a quaternion (in radians). Axis is stored in
///the Vector4's xyz and the angle is stored in the w. Axis is assumed to be 
///normalized.
Quaternion ToQuaternion(Vec4Param axisAngle);
void ToQuaternion(Vec4Param axisAngle, QuatPtr quaternion);

///Converts an axis-angle pair to a quaternion (in radians). Axis is assumed to
///be normalized.
Quaternion ToQuaternion(Vec3Param axis, real radians);
void ToQuaternion(Vec3Param axis, real radians, QuatPtr quaternion);

///Convert a set of Euler angles to a quaternion (in radians).
Quaternion ToQuaternion(Vec3Param eulerVector);

///Convert a set of Euler angles to a quaternion (in radians).
Quaternion ToQuaternion(EulerAnglesParam eulerAngles);
void ToQuaternion(EulerAnglesParam eulerAngles, QuatPtr quaternion);

///Converts a 3x3 matrix to a quaternion (in radians).
Quaternion ToQuaternion(Mat3Param matrix);
void ToQuaternion(Mat3Param matrix, QuatPtr quaternion);

///Converts a 4x4 matrix to a quaternion (in radians).
Quaternion ToQuaternion(Mat4Param matrix);
void ToQuaternion(Mat4Param matrix, QuatPtr quaternion);

Quaternion ToQuaternion(Vec3Param facing, Vec3Param up);
Quaternion ToQuaternion(Vec3Param facing, Vec3Param up, Vec3Param right);
///Generates a quaternion from the x,y,z axis angles.
Quaternion ToQuaternion(real x, real y, real z);
///Generates the quaternion that rotates start to end.
Quaternion RotationQuaternionBetween(Vec3Param start, Vec3Param end);

///Generates a vector perpendicular to the given vector. The result is not normalized.
Vec2 GeneratePerpendicularVector(Vec2Param input);
///Generates a vector perpendicular to the given vector. The result is not normalized.
Vec3 GeneratePerpendicularVector(Vec3Param input);

///Generates a set of orthonormal vectors from the given vectors, modifying u 
///and v.
void GenerateOrthonormalBasis(Vec3Param w, Vec3Ptr u, Vec3Ptr v);

///Doesn't blow up on zero vectors
void DebugGenerateOrthonormalBasis(Vec3Param w, Vec3Ptr u, Vec3Ptr v);

///Converts a 32-bit float into a compressed 16-bit floating point value;
///referenced from Insomniac Games math library.
half ToHalf(float value);

///Converts a 16-bit compressed floating point value back into a 32-bit float;
///referenced from Insomniac Games math library.
float ToFloat(half value);

//----------------------------------------------------------- Rotation Functions
/// Computes the angle about the z-axis between the vector and the x-axis
real Angle2D(Vec3Param a);

/// Rotate a vector towards another changing at most maxAngle (radians).
Vector2 RotateTowards(Vec2Param a, Vec2Param b, real maxAngle);
/// Rotate a vector towards another changing at most maxAngle (radians).
Vector3 RotateTowards(Vec3Param a, Vec3Param b, real maxAngle);
/// Rotate a quaternion towards another changing at most maxAngle (radians).
Quat RotateTowards(QuatParam a, QuatParam b, real maxAngle);

/// Same as RotateTowards except this function deals correctly with
/// invalid vectors. Used for binding to scripting languages.
Vector2 SafeRotateTowards(Vec2Param a, Vec2Param b, real maxAngle);
/// Same as RotateTowards except this function deals correctly with
/// invalid vectors. Used for binding to scripting languages.
Vector3 SafeRotateTowards(Vec3Param a, Vec3Param b, real maxAngle);

/// Get the rotation angle between two vectors in radians.
real SignedAngle(Vec3Param a, Vec3Param b, Vec3Param up);

/// Rotate a vector about an axis by the given angle.
Vector3 RotateVector(Vec3Param a, Vec3Param axis, real radians);

/// Converts Euler degrees to a quaternion.
Quat EulerDegreesToQuat(Vec3Param eulerDegrees);

/// Converts a quaternion to Euler degrees.
Vector3 QuatToEulerDegrees(QuatParam rotation);

//----------------------------------------------------------- Misc Functions
float Luminance(Vector3 linearColor);

}// namespace Math
