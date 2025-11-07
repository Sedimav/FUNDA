cmake_minimum_required(VERSION 3.10)
project(lab6 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

add_executable(lab6 main.c func.c)
