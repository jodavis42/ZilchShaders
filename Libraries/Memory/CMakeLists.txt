set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_library(Memory "")

include(${CMAKE_CURRENT_LIST_DIR}/CMakeFiles.cmake)
target_sources(Memory
    PRIVATE
    ${manualAdditions}
)

target_include_directories(Memory
    PUBLIC
    ${CurrentDirectory}
    ${LibrariesDir}
)

ADD_MSVC_PRECOMPILED_HEADER(Memory "Precompiled.hpp" "Precompiled.cpp")
Set_Common_TargetCompileOptions(Memory)

target_link_libraries(Memory
                      PUBLIC
                      Foundation
                      FixedContainers
)

set_target_properties(Memory PROPERTIES FOLDER "Libraries")
