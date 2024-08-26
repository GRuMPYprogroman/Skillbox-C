from setuptools import setup, Extension
import pybind11

# Получаем путь к заголовочным файлам pybind11
include_dirs = [pybind11.get_include()]

# Определяем расширение для компиляции
ext_modules = [
    Extension(
        'SmartPtr_hw',  # Имя модуля
        ['src/Vector3D.cpp'],  # Исходные файлы
        include_dirs=include_dirs,  # Пути к заголовочным файлам
        language='c++',  # Язык сборки
        extra_compile_args=['-std=c++17']  # Используем стандарт C++17
    ),
]

# Конфигурация сборки
setup(
    name='SmartPtr_hw',
    version='0.1',
    author='Лазарев С.П',
    description='Python модуль для работы с векторной алгеброй',
    ext_modules=ext_modules,
    include_dirs=include_dirs,  # Добавлено: включение заголовочных файлов pybind11
    zip_safe=False,  # Добавлено: для обеспечения правильной работы C++ расширений
)