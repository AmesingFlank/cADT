cmake_minimum_required(VERSION 3.10)
project(cADT)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -O0")

set(CMAKE_CXX_STANDARD 17)

add_executable(cADT main.cpp cADT.h)