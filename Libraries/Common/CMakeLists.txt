set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_library(Common "")

set(manualAdditions "")
if ("${CMAKE_GENERATOR}" MATCHES "Visual Studio*")
    set(manualAdditions "${CMAKE_CURRENT_LIST_DIR}/ZeroVisualizers.natvis")
endif()

include(${CMAKE_CURRENT_LIST_DIR}/CMakeFiles.cmake)
target_sources(Common
    PRIVATE
    ${manualAdditions}
)

target_include_directories(Common 
    PUBLIC
    ${CurrentDirectory}
    ${ZeroLibrariesDir}
)

ADD_MSVC_PRECOMPILED_HEADER(Common "Precompiled.hpp" "Precompiled.cpp")
Set_Common_TargetCompileOptions(Common)

target_link_libraries(Common
                      PUBLIC
                      Foundation
                      Memory
                      Math
)

set_target_properties(Common PROPERTIES FOLDER "Libraries")