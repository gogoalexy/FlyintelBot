cmake_minimum_required (VERSION 2.8)
project (flypixy CXX)

set (CMAKE_EXECUTABLE_SUFFIX ".out")
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/src/cmake" )

add_subdirectory(src)

add_executable (flypixy flypixy.cpp)
