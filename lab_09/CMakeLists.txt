cmake_minimum_required(VERSION 3.10)

project(lab9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab09
        1.cpp
        2.cpp
)

target_include_directories(lab09 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})