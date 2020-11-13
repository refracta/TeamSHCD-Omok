cmake_minimum_required(VERSION 3.10)
project(BoardGame C)

set(CMAKE_C_STANDARD 99)

file(GLOB PROJECT_C_FILES "*.c")

file(GLOB PROJECT_HEADER_FILES "inc/*.h")

add_executable(BoardGame ${PROJECT_C_FILES} ${PROJECT_HEADER_FILES})