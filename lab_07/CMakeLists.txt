cmake_minimum_required(VERSION 4.0.2)
project(Lab07)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab07
        1.cpp
        2.cpp
        3.cpp
)

target_include_directories(lab07 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})