################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################

add_library(Platform "")

include(${CMAKE_CURRENT_LIST_DIR}/Generated.cmake)



target_include_directories(Platform 
    PUBLIC
    ${CurrentDirectory}
    ${CurrentDirectory}/Windows
    ${ZeroLibrariesDir}
)

ADD_MSVC_PRECOMPILED_HEADER(Platform "Precompiled.hpp" "Precompiled.cpp")
Set_Common_TargetCompileOptions(Platform)

target_link_libraries(Platform
                      PUBLIC
                      Common
)

set_target_properties(Platform PROPERTIES FOLDER "Libraries")
