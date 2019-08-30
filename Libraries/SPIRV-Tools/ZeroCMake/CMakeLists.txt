################################################################################
# Author: Joshua Davis
# Copyright 2018, DigiPen Institute of Technology
################################################################################
# get our parent directory
get_filename_component(ParentDirectory ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

# get our current directory
set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})
set(SPIRV-Tools-Dir ${CMAKE_CURRENT_LIST_DIR}/..)

if(use_spirv_shared_library)
  set(SpirVToolsCompileOptions
        -DSPIRV_TOOLS_IMPLEMENTATION
        -DSPIRV_TOOLS_SHAREDLIB
  )
endif()

################################################################################
# define all of the libraries that are in this folder
################################################################################
add_library(SPIRV-Tools "")

if (use_spirv_shared_library)
  add_library(SPIRV-Tools-opt SHARED "")
else ()
  add_library(SPIRV-Tools-opt "")
endif ()
  
################################################################################
# Explicitly define the folders as they are not organized how we want
################################################################################
set_target_properties(SPIRV-Tools PROPERTIES FOLDER "SPIRV")
set_target_properties(SPIRV-Tools-opt PROPERTIES FOLDER "SPIRV")

################################################################################
# include filelists for each library
################################################################################
include(SPIRV-Tools.cmake)
include(SPIRV-Tools-opt.cmake)

################################################################################
# define include directories for all of our libraries
################################################################################
target_include_directories(SPIRV-Tools 
    PUBLIC 
        ${SPIRV-Tools-Dir}/generated
        ${SPIRV-Tools-Dir}/external/SPIRV-Headers
        ${SPIRV-Tools-Dir}/external/SPIRV-Headers/include
        ${SPIRV-Tools-Dir}/external/SPIRV-Headers/include/spirv
        ${SPIRV-Tools-Dir}/include
        ${SPIRV-Tools-Dir}/include/spirv-tools
        ${SPIRV-Tools-Dir}/source
        ${SPIRV-Tools-Dir}/source/comp
        ${SPIRV-Tools-Dir}/source/link
        ${SPIRV-Tools-Dir}/source/opt
        ${SPIRV-Tools-Dir}/source/util
        ${SPIRV-Tools-Dir}/source/val
        ${SPIRV-Tools-Dir}/tools
        ${SPIRV-Tools-Dir}/tools/as
        ${SPIRV-Tools-Dir}/tools/cfg
        ${SPIRV-Tools-Dir}/tools/comp
        ${SPIRV-Tools-Dir}/tools/dis
        ${SPIRV-Tools-Dir}/tools/link
        ${SPIRV-Tools-Dir}/tools/opt
        ${SPIRV-Tools-Dir}/tools/stats
        ${SPIRV-Tools-Dir}/tools/val
        ${SPIRV-Tools-Dir}

)
target_include_directories(SPIRV-Tools-opt
    PUBLIC 
        ${SPIRV-Tools-Dir}/generated
        ${SPIRV-Tools-Dir}/external/SPIRV-Headers
        ${SPIRV-Tools-Dir}/external/SPIRV-Headers/include
        ${SPIRV-Tools-Dir}/external/SPIRV-Headers/include/spirv
        ${SPIRV-Tools-Dir}/include
        ${SPIRV-Tools-Dir}/include/spirv-tools
        ${SPIRV-Tools-Dir}/source
        ${SPIRV-Tools-Dir}/source/comp
        ${SPIRV-Tools-Dir}/source/link
        ${SPIRV-Tools-Dir}/source/opt
        ${SPIRV-Tools-Dir}/source/util
        ${SPIRV-Tools-Dir}/source/val
        ${SPIRV-Tools-Dir}/tools
        ${SPIRV-Tools-Dir}/tools/as
        ${SPIRV-Tools-Dir}/tools/cfg
        ${SPIRV-Tools-Dir}/tools/comp
        ${SPIRV-Tools-Dir}/tools/dis
        ${SPIRV-Tools-Dir}/tools/link
        ${SPIRV-Tools-Dir}/tools/opt
        ${SPIRV-Tools-Dir}/tools/stats
        ${SPIRV-Tools-Dir}/tools/val
        ${SPIRV-Tools-Dir}
)

################################################################################
# set the linked libraries for all of our targets
################################################################################
target_link_libraries(SPIRV-Tools
                      PUBLIC
)
target_link_libraries(SPIRV-Tools-opt
                      PUBLIC
                      SPIRV-Tools
)
Set_Common_TargetCompileOptions(SPIRV-Tools)
Set_Common_TargetCompileOptions(SPIRV-Tools-opt)
