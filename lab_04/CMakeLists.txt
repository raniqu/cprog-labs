cmake_minimum_required(VERSION 4.0.2)
project(Lab04)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
        1.cpp
        2.cpp
        3.cpp
        4.cpp
        5.cpp
        6.cpp
        7.cpp
        8.cpp
)
add_executable(lab04 ${SOURCE_FILES})

target_include_directories(lab04 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})