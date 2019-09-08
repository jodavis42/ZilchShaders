set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_executable(ZilchShadersTests "")

include(${CurrentDirectory}/CMakeFiles.cmake)

target_include_directories(ZilchShadersTests 
    PUBLIC 
        ${CurrentDirectory}
        ${CurrentDirectory}/../
)

set_target_properties(ZilchShadersTests PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CurrentDirectory}/")
Set_Common_TargetCompileOptions(ZilchShadersTests)

target_link_libraries(ZilchShadersTests
                      PUBLIC
                      ZilchShaders
                      OpenGL
                      GLU
                      Glew32
)

set_target_properties(ZilchShadersTests PROPERTIES FOLDER "Applications")
