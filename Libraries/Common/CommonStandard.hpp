///////////////////////////////////////////////////////////////////////////////
/// 
/// Authors: Joshua Davis
/// Copyright 2016, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

// The first thing we do is detect the platform.
// The next thing we do is define macros that all platforms may use
// We also ignore any compiler or platform specific warnings here
#include "Platform.hpp"

#include <algorithm>
#include <ctype.h>
#include <cstddef>
#include <utility>
#include <typeinfo>
#include <new>
#include <stdarg.h>
#include <climits>
#include <string>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include <setjmp.h>
#include <ctime>
#include <limits>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <cstdio>
#include <cstdlib>
#include <cfloat>
#include <malloc.h>

namespace Zero
{

class ZeroNoImportExport CommonLibrary
{
public:
  static void Initialize();
  static void Shutdown();
};

}//namespace Zero

#include "Foundation/Typedefs.hpp"
#include "Foundation/Standard.hpp"
#include "Foundation/Determinism.hpp"
#include "Foundation/Diagnostic.hpp"
#include "Foundation/EnumDeclaration.hpp"
#include "Foundation/BitField.hpp"

#include "FixedContainers/InList.hpp"

#include "Memory/Memory.hpp"
#include "Memory/Stats.hpp"
#include "Memory/Allocator.hpp"
#include "Memory/AllocationContainer.hpp"
#include "Memory/GraphNode.hpp"
#include "Memory/Root.hpp"
#include "Memory/Heap.hpp"
#include "Memory/LocalStackAllocator.hpp"
#include "Memory/TypedAllocator.hpp"


#include "Time.hpp"
#include "Utility/Misc.hpp"
#include "Utility/Guid.hpp"
#include "Containers/TypeTraits.hpp"
#include "Utility/BitTypes.hpp"
#include "Utility/BitMath.hpp"
#include "Platform/Atomic.hpp"
#include "Containers/ArrayMap.hpp"
#include "Containers/ArraySet.hpp"
#include "Containers/BlockArray.hpp"
#include "Containers/ByteBuffer.hpp"
#include "Containers/CyclicArray.hpp"
#include "Containers/OwnedArray.hpp"
#include "Containers/SortedArray.hpp"
#include "Containers/UnsortedMap.hpp"
#include "Containers/OrderedHashMap.hpp"
#include "Containers/OrderedHashSet.hpp"
#include "Diagnostic/Console.hpp"
#include "Containers/Algorithm.hpp"
#include "Containers/Allocator.hpp"
#include "Containers/Array.hpp"
#include "Containers/BitStream.hpp"
#include "Containers/ContainerCommon.hpp"
#include "Containers/Hashing.hpp"
#include "Containers/HashMap.hpp"
#include "Containers/HashSet.hpp"
#include "Containers/SlotMap.hpp"
#include "Memory/Block.hpp"
#include "Memory/LocalStackAllocator.hpp"
#include "Memory/Pool.hpp"
#include "Memory/Stack.hpp"
#include "String/Rune.hpp"
#include "String/String.hpp"
#include "String/CharacterTraits.hpp"
#include "String/StringRange.hpp"
#include "String/StringConversion.hpp"
#include "String/StringBuilder.hpp"
#include "String/StringUtility.hpp"
#include "String/ToString.hpp"
#include "Containers/BitStream.hpp"
#include "Regex/Regex.hpp"
#include "Utility/Guid.hpp"
#include "Utility/TextStream.hpp"
#include "Utility/HalfFloat.hpp"
#include "Utility/MaxSizeof.hpp"
#include "VirtualAny.hpp"
#include "Utility/IdStore.hpp"
#include "Utility/ItemCache.hpp"
#include "Utility/Log2.hpp"
#include "Utility/Status.hpp"
#include "Utility/ForEachRange.hpp"
#include "Utility/Misc.hpp"
#include "Utility/UintNType.hpp"
#include "Utility/UniquePointer.hpp"
#include "Utility/HalfFloat.hpp"
#include "Lexer/Lexer.hpp"
#include "Utility/Guid.hpp"
#include "Utility/NativeType.hpp"
#include "Utility/Variant.hpp"
#include "Utility/SpinLock.hpp"
#include "Utility/Stream.hpp"
#include "Singleton.hpp"

#include "Math/Reals.hpp"
#include "Math/MatrixStorage.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"
#include "Math/Matrix2.hpp"
#include "Math/Matrix3.hpp"
#include "Math/Matrix4.hpp"
#include "Math/IntVector2.hpp"
#include "Math/IntVector3.hpp"
#include "Math/IntVector4.hpp"
#include "Math/BoolVector2.hpp"
#include "Math/BoolVector3.hpp"
#include "Math/BoolVector4.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Math.hpp"
#include "Math/SharedVectorFunctions.hpp"

#include "Math/ByteColor.hpp"
#include "Math/EulerOrder.hpp"
#include "Math/EulerAngles.hpp"

namespace Zero
{
#include "Math/MathImports.hpp"
}

#include "Random.hpp"

#include "Platform/PrivateImplementation.hpp"
#include "Platform/Utilities.hpp"
#include "Platform/OsHandle.hpp"
#include "Platform/Thread.hpp"
#include "Platform/ThreadSync.hpp"
#include "Platform/ExternalLibrary.hpp"
#include "Platform/File.hpp"
#include "Platform/FileEvents.hpp"
#include "Platform/FilePath.hpp"
#include "Platform/FileSystem.hpp"
#include "Platform/Lock.hpp"
#include "Platform/Process.hpp"
#include "Platform/SocketEnums.hpp"
#include "Platform/SocketConstants.hpp"
#include "Platform/Socket.hpp"
#include "Platform/Timer.hpp"
#include "Platform/TimerBlock.hpp"
#include "Platform/Intrinsics.hpp"

#include "ThreadableLoop.hpp"
