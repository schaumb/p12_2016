cmake_minimum_required(VERSION 3.6)
project(1_feladat_terkep_illesztes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -static-libgcc -static-libstdc++")

set(SOURCE_FILES main.cpp lodepng.h lodepng.cpp)
add_executable(1_feladat_terkep_illesztes ${SOURCE_FILES})