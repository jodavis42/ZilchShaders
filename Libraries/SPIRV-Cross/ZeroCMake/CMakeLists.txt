################################################################################
# Author: Joshua Davis
# Copyright 2018, DigiPen Institute of Technology
################################################################################
# get our parent directory
get_filename_component(ParentDirectory ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

# get our current directory
set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})
set(SPIRV-Cross-Dir ${CMAKE_CURRENT_LIST_DIR}/..)

################################################################################
# define all of the libraries that are in this folder
################################################################################
add_library(SPIRV-Cross "")


################################################################################
# Explicitly define the folders as they are not organized how we want
################################################################################
set_target_properties(SPIRV-Cross PROPERTIES FOLDER "SPIRV")

################################################################################
# include filelists for each library
################################################################################
include(SPIRV-Cross.cmake)

################################################################################
# define include directories for all of our libraries
################################################################################
target_include_directories(SPIRV-Cross 
    PUBLIC 
        ${CurrentDirectory}/SPIRV-Cross
        ${CurrentDirectory}

)

################################################################################
# set the linked libraries for all of our targets
################################################################################
target_link_libraries(SPIRV-Cross
                      PUBLIC
)
Set_Common_TargetCompileOptions(SPIRV-Cross)
