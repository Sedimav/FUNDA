cmake_minimum_required(VERSION 3.10)
project(lab5)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(lab5 main.c src/func.c)
target_include_directories(lab5 PRIVATE include)
