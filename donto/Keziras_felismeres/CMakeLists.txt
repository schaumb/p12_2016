cmake_minimum_required(VERSION 3.6)
project(Keziras_felismeres)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -static-libgcc -static-libstdc++")

set(SOURCE_FILES main.cpp Sample.cpp Sample.hpp)
add_executable(Keziras_felismeres ${SOURCE_FILES})