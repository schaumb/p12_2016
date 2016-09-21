cmake_minimum_required(VERSION 3.2)
project(Ko_papir_ollo_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -static-libgcc -static-libstdc++")

find_library(ws2_32_LIBRARY_PATH ws2_32)

set(SOURCE_FILES main.cpp ../NetworkMagic.hpp ../NetworkMagic.cpp AI.cpp AI.hpp Tactic.cpp Tactic.hpp)
add_executable(Ko_papir_ollo_client ${SOURCE_FILES})
target_link_libraries(Ko_papir_ollo_client ${ws2_32_LIBRARY_PATH})