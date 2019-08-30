################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_library(Zilch "")

include(${CMAKE_CURRENT_LIST_DIR}/Generated.cmake)

target_sources(Zilch
    PRIVATE
)

target_include_directories(Zilch 
    PUBLIC
    ${CurrentDirectory}
    ${CurrentDirectory}/../
    ${ZeroLibrariesDir}
)

ADD_MSVC_PRECOMPILED_HEADER(Zilch "Zilch.hpp" "Zilch.cpp")
Set_Common_TargetCompileOptions(Zilch)

target_link_libraries(Zilch
                      PUBLIC
                      Common
                      Platform
                      Math
)

set_target_properties(Zilch PROPERTIES FOLDER "Libraries")

