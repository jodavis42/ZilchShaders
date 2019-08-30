set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_library(Foundation "")

include(${CMAKE_CURRENT_LIST_DIR}/CMakeFiles.cmake)
target_sources(Foundation
    PRIVATE
    ${manualAdditions}
)

target_include_directories(Foundation 
    PUBLIC
    ${CurrentDirectory}
    ${LibrariesDir}
)

ADD_MSVC_PRECOMPILED_HEADER(Foundation "Precompiled.hpp" "Precompiled.cpp")
Set_Common_TargetCompileOptions(Foundation)

target_link_libraries(Foundation
                      PUBLIC
)

set_target_properties(Foundation PROPERTIES FOLDER "Libraries")
