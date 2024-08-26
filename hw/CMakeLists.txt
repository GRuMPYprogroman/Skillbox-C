cmake_minimum_required(VERSION 3.16)
project(SmartPtr_hw)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python COMPONENTS Interpreter Development REQUIRED)

add_subdirectory(libs/pybind11)

pybind11_add_module(SmartPtr_hw src/Vector3D.h src/Vector3D.cpp)

#add_executable(SmartPtr)

#set(sources
#    main.cpp
#    Vector3D.h
#    Vector3D.cpp
#)

#target_sources(SmartPtr PUBLIC ${sources})
