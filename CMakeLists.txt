cmake_minimum_required(VERSION 3.22)
project(cshell C)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/include/readline)

file(GLOB_RECURSE SOURCES src/*)

add_executable(cshell ${SOURCES})

target_include_directories(cshell PUBLIC include/)
target_link_libraries(cshell readline)