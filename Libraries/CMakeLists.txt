set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

set(LibrariesDir ${CurrentDirectory})

add_subdirectory(Foundation)
add_subdirectory(FixedContainers)
add_subdirectory(Memory)
add_subdirectory(Math)

add_subdirectory(Common)
add_subdirectory(Platform)

add_subdirectory(Zilch)
add_subdirectory(ZilchShaders)

add_subdirectory(SPIRV-Cross/ZeroCMake)
add_subdirectory(SPIRV-Tools/ZeroCMake)
