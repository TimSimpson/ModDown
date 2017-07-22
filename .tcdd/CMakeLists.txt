# *********************************************************************
# Mod Down
#   Translates header files with markdown in them to one big
#   markdown document.
# *********************************************************************
project(lp3_moddown CXX)
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

add_library(Lp3_ModDown
    ${CMAKE_CURRENT_SOURCE_DIR}/include/moddown.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/moddown.cpp
)

target_include_directories(Lp3_ModDown
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        src)

install(TARGETS Lp3_ModDown EXPORT Lp3_ModDown_Config
    ARCHIVE  DESTINATION lib
    LIBRARY  DESTINATION lib
    RUNTIME  DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)

install(EXPORT Lp3_ModDown_Config DESTINATION share/Lp3_ModDown/cmake)

export(TARGETS Lp3_ModDown FILE Lp3_ModDown_Config.cmake)

add_executable(moddown ${CMAKE_CURRENT_SOURCE_DIR}/src/moddown-cli.cpp)
target_link_libraries(moddown Lp3_ModDown)

if (LP3_SETUP_FOLDERS)
    set_target_properties (Lp3_ModDown PROPERTIES FOLDER ModDown)
    set_target_properties (moddown PROPERTIES FOLDER ModDown)
endif()
