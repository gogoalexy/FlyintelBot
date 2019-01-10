#
#	  This file is part of FlyintelBot.
#    Copyright (C) 2018  Alex Huang-Yu Yao
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 2.8)
project (flypixy CXX)

set (CMAKE_EXECUTABLE_SUFFIX ".out")
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" )
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR/..})

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
target_link_libraries (DCmotor pthread)
target_link_libraries (Sharp_IR wiringPi)
target_link_libraries (HC_SR04 wiringPi)
target_link_libraries (flypixy wiringPi DCmotor Sharp_IR HC_SR04 attention sensefilter flyintel)
