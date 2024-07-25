cmake_minimum_required(VERSION 3.30)
project(
    hw_1
    VERSION 1.0
    DESCRIPTION "First homework"
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Release)

add_executable(hw_1)
#add_library(lesson4)

set(sources
    main.cpp
)

target_sources(hw_1 PRIVATE ${sources})