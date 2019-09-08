set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_library(Glew32 STATIC IMPORTED GLOBAL)
set_target_properties(Glew32 PROPERTIES IMPORTED_LOCATION_DEBUG ${CurrentDirectory}/Glew/lib/Windows/x86/Debug/glew32s.lib)
set_target_properties(Glew32 PROPERTIES IMPORTED_LOCATION_RELEASE ${CurrentDirectory}/Glew/lib/Windows/x86/Release/glew32s.lib)
target_include_directories(Glew32 INTERFACE ${CurrentDirectory} ${CurrentDirectory}/Glew/include)
target_include_directories(Glew32 INTERFACE ${CurrentDirectory} ${CurrentDirectory}/Glew/include/GL)

add_library(OpenGL STATIC IMPORTED GLOBAL)
set_target_properties(OpenGL PROPERTIES IMPORTED_LOCATION ${CurrentDirectory}/GL/lib/Windows/x86/OpenGL32.lib)
target_include_directories(OpenGL INTERFACE ${CurrentDirectory} ${CurrentDirectory}/GL/include)

add_library(GLU STATIC IMPORTED GLOBAL)
set_target_properties(GLU PROPERTIES IMPORTED_LOCATION ${CurrentDirectory}/GL/lib/Windows/x86/GlU32.lib)
target_include_directories(GLU INTERFACE ${CurrentDirectory} ${CurrentDirectory}/GL/include)
