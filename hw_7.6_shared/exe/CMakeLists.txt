cmake_minimum_required(VERSION 3.16)
project(MatrixLibTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

set(MATH_USE_DOUBLE_PRECISION "Use double precision" ON)

set(sources
    main.cpp
)


link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/matrixlib)

add_executable(MatrixLibTest ${sources})

target_link_libraries(MatrixLibTest ${CMAKE_CURRENT_SOURCE_DIR}/libs/matrixlib/shared-matrixlib.so)