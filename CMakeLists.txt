cmake_minimum_required(VERSION 3.22)
project(cshell C)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/include/readline)

add_executable(cshell src/main.c src/internal_cmds.c src/core.h src/core.c include/definitions.h src/args.h src/args.c)

target_include_directories(cshell PUBLIC include/)
target_link_libraries(cshell readline)