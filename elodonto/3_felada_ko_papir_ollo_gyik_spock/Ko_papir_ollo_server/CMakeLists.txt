cmake_minimum_required(VERSION 3.4)
project(Ko_papir_ollo_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

find_library(ws2_32_LIBRARY_PATH ws2_32)

set(SOURCE_FILES main.cpp ../NetworkMagic.hpp ../NetworkMagic.cpp ../RPSLS.hpp ../RPSLS.cpp)
add_executable(Ko_papir_ollo_server ${SOURCE_FILES})
target_link_libraries(Ko_papir_ollo_server ${ws2_32_LIBRARY_PATH})