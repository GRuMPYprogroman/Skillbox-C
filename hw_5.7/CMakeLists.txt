cmake_minimum_required(VERSION 3.16)        # требуемая версия cmake
project(hw5)
   
set(CMAKE_CXX_STANDARD 17)                  # устанавливаем требуемый стандарт языка (это значит, что в проекте буду использоваться фичи этоо стандарта)
set(CMAKE_CXX_STANDARD_REQUIRED ON)         # при сборке платформа будет проверять поддержку стандарта C++17 компилятором

set(CMAKE_BUILD_TYPE Debug)                 # конфигурация сборки - Debug

add_executable(hw5)                     # эта команда сообщает платформе сборке, что код будет компилироваться в исполняемый файл с названием lesson3.exe

set(sources                                 # создаем cmake-переменную sources, которая содержит список файлов исходного когда (в данном случае main.cpp)
    src/main.cpp
)

set(headers
    include/Car.h
)

target_sources(hw5 PRIVATE ${sources} ${headers})   # команда указывает компилятору, что исполняемый файл будет компилироваться из исходников, перечисленных в sources