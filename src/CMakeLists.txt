cmake_minimum_required(VERSION 2.8)
project (flypixy CXX)

set (CMAKE_EXECUTABLE_SUFFIX ".out")
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" )

add_executable (flypixy flypixy.cpp)

add_library(sensefilter sensefilter.cpp)
add_library(DCmotor DCmotor.cpp)
add_library(Sharp_IR Sharp_IR.cpp)
add_library(HC_SR04 HC_SR04.cpp)
add_library(flyintel flyintel.cpp)
add_library(attention attention.cpp)

# libpixyusb should always come before libboost and libusb #
target_link_libraries (attention pixyusb)

find_package ( libpixyusb REQUIRED )
find_package ( libusb-1.0 REQUIRED )
find_package ( Boost 1.49 COMPONENTS thread system chrono REQUIRED)

target_link_libraries (attention ${Boost_LIBRARIES})
target_link_libraries (attention ${LIBUSB_1_LIBRARY})

file(STRINGS "cmake/VERSION" LIBPIXY_VERSION)
add_definitions(-D__LIBPIXY_VERSION__="${LIBPIXY_VERSION}")

include_directories (.
                     include
                     ${Boost_INCLUDE_DIR}
                     ${LIBUSB_1_INCLUDE_DIRS})

target_link_libraries (DCmotor wiringPi)
