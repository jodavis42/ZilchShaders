################################################################################
# Author: Joshua Shlemmer
# Copyright 2017, DigiPen Institute of Technology
################################################################################
# get our parent directory
get_filename_component(ParentDirectory ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
# get our current directory
set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})


#add_library(Platform "")

# based on the set platform variable, include the correct definition of the platform target
#if ("${platform_library}" STREQUAL "Windows")
  add_subdirectory(Windows)
    #include(Windows.cmake)
#elseif ("${platform_library}" STREQUAL "Posix")
#    include(Posix.cmake)
#elseif ("${platform_library}" STREQUAL "SDL")
#    include(SDL.cmake)
#elseif ("${platform_library}" STREQUAL "STL")
#    include(STL.cmake)
#elseif ("${platform_library}" STREQUAL "SDLSTLEmpty")
#    include(SDLSTLEmpty.cmake)
#elseif ("${platform_library}" STREQUAL "Emscripten")
#    include(Emscripten.cmake)
# if we are not given a known platform (or empty is selected) try the empty platform
#else()
#    include(Empty.cmake)
#endif()

#target_sources(Platform
#PRIVATE
#    ${manualAdditions}
#)

#target_include_directories(Platform 
#    PUBLIC
#    ${CurrentDirectory}
#    ${CurrentDirectory}/Windows
#    ${ZeroLibrariesDir}
#)
#
##ADD_MSVC_PRECOMPILED_HEADER(Platform "Precompiled.hpp" "Precompiled.cpp")
#
#target_link_libraries(Platform
#                      PUBLIC
#                      Common
#)


