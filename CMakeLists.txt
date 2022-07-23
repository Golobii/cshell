cmake_minimum_required(VERSION 3.22)
project(cshell C)

set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(cshell src/main.c src/internal_cmds.c src/core.h src/core.c include/definitions.h src/args.h src/args.c)

target_include_directories(cshell PUBLIC include/)
target_link_libraries(cshell ${CURSES_LIBRARIES})