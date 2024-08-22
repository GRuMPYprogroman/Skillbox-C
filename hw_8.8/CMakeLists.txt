cmake_minimum_required(VERSION 3.16)
project(Qt_hw)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(sources
    main.cpp
    snake.h
    snake.cpp
)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(Snake ${sources})

target_link_libraries(Snake PRIVATE Qt5::Core Qt5::Widgets)
