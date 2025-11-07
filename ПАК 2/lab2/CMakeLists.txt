cmake_minimum_required(VERSION 3.10)
project(lab2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(SOURCES
    main.c
    func.c 
    f2unc.c
)

add_executable(lab2 ${SOURCES})

add_custom_target(run
    COMMAND ./lab2
    DEPENDS lab2
    COMMENT "Запуск программы lab2"
)