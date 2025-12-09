cmake_minimum_required(VERSION 4.0.2)
project(Lab05)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)
add_executable(lab05 implementation.cpp)