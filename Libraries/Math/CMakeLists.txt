set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_library(Math "")

include(${CMAKE_CURRENT_LIST_DIR}/CMakeFiles.cmake)
target_sources(Math
    PRIVATE
    ${manualAdditions}
)

target_include_directories(Math
    PUBLIC
    ${CurrentDirectory}
    ${LibrariesDir}
)

ADD_MSVC_PRECOMPILED_HEADER(Math "Precompiled.hpp" "Precompiled.cpp")
Set_Common_TargetCompileOptions(Math)

target_link_libraries(Math
                      PUBLIC
                      Foundation
)

set_target_properties(Math PROPERTIES FOLDER "Libraries")
