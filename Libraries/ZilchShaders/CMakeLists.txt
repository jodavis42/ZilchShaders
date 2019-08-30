set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_library(ZilchShaders "")

include(${CMAKE_CURRENT_LIST_DIR}/CMakeFiles.cmake)
target_sources(ZilchShaders
    PRIVATE
    ${manualAdditions}
)

set(SpirVDir ${CurrentDirectory}/../SpirV)

target_include_directories(ZilchShaders 
    PUBLIC
    ${CurrentDirectory}
    ${ZeroLibrariesDir}
    ${CurrentDirectory}/../
    ${SpirVDir}/SPIRV-Cross
    ${SpirVDir}/SpirVFiles
    ${SpirVDir}/SpirVFiles/external
    ${SpirVDir}/SpirVFiles/external/SPIRV-Headers/include
    ${SpirVDir}/SpirVFiles/include
    ${SpirVDir}/SpirVFiles/include/spirv-tools
    ${SpirVDir}/SpirVFiles/build
    ${SpirVDir}/SpirVFiles/tools
    ${SpirVDir}/SpirVFiles/source
)

ADD_MSVC_PRECOMPILED_HEADER(ZilchShaders "Precompiled.hpp" "Precompiled.cpp")
Set_Common_TargetCompileOptions(ZilchShaders)

target_link_libraries(ZilchShaders
                      PUBLIC
                      Common
                      Zilch
                      SPIRV-Cross
                      SPIRV-Tools
                      SPIRV-Tools-opt
)

set_target_properties(ZilchShaders PROPERTIES FOLDER "Libraries")
