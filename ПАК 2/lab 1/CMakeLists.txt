cmake_minimum_required(VERSION 3.10)
project(lab01)

add_executable(lab01 main.c func.c)
target_link_libraries(lab01 m)
