cmake_minimum_required(VERSION 4.0.2)
project(Lab06)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab06
        lab06.cpp
        1.cpp
        2.cpp
        3.cpp
        4.cpp
        5.cpp
        6.cpp
        7.cpp
        8.cpp
        9.cpp
)

target_include_directories(lab06 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})