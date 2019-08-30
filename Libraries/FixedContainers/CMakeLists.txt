set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_library(FixedContainers "")

include(${CMAKE_CURRENT_LIST_DIR}/CMakeFiles.cmake)
target_sources(FixedContainers
    PRIVATE
    ${manualAdditions}
)

target_include_directories(FixedContainers
    PUBLIC
    ${CurrentDirectory}
    ${LibrariesDir}
)

ADD_MSVC_PRECOMPILED_HEADER(FixedContainers "Precompiled.hpp" "Precompiled.cpp")
Set_Common_TargetCompileOptions(FixedContainers)

target_link_libraries(FixedContainers
                      PUBLIC
                      Foundation
)

set_target_properties(FixedContainers PROPERTIES FOLDER "Libraries")
