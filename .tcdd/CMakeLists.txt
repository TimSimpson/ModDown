# *********************************************************************
# Markule
#   Translates header files with markdown in them to one big
#   markdown document.
# *********************************************************************
project(lp3_markule CXX)
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

###############################################################################
#  Third Party libraries
###############################################################################

set(DEPS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/deps")

{{ cmake_deps }}

###############################################################################
#  Lib
###############################################################################

add_library(Lp3_Markule
    ${CMAKE_CURRENT_SOURCE_DIR}/include/markule.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/markule.cpp
)

target_include_directories(Lp3_Markule
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        src)

install(TARGETS Lp3_Markule EXPORT Lp3_Markule_Config
    ARCHIVE  DESTINATION lib
    LIBRARY  DESTINATION lib
    RUNTIME  DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)

install(EXPORT Lp3_Markule_Config DESTINATION share/Lp3_Markule/cmake)

export(TARGETS Lp3_Markule FILE Lp3_Markule_Config.cmake)

target_link_libraries(Lp3_Markule lp3_deps::boost Boost::filesystem
                      lp3_deps::gsl)

###############################################################################
#  exe
###############################################################################

add_executable(markule ${CMAKE_CURRENT_SOURCE_DIR}/src/markule-cli.cpp)
target_link_libraries(markule Lp3_Markule)
