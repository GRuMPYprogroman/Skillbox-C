cmake_minimum_required(VERSION 3.16)
project(MatrixLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

set(MATH_USE_DOUBLE_PRECISION "Use double precision" ON)

# Добавляем исходные файлы
set(SOURCES
    matrix.h
    matrix.cpp
    c_api.cpp
    c_api.h
 )

 include(GenerateExportHeader)


# Создаем динамическую библиотеку
add_library(shared-matrixlib SHARED ${SOURCES})

# Указываем директорию с заголовочными файлами
target_include_directories(shared-matrixlib
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
)

target_compile_definitions(
    shared-matrixlib
    PUBLIC
        "$<$<BOOL:${MATH_USE_DOUBLE_PRECISION}>:MATH_DOUBLE_PREC_DEFINE>"
)

set_target_properties(shared-matrixlib PROPERTIES PREFIX "")

generate_export_header(
    shared-matrixlib
    EXPORT_FILE_NAME "${PROJECT_BINARY_DIR}/export_shared.h"
    BASE_NAME matrixlib
)