cmake_minimum_required(VERSION 3.10)
project(BoardGame C)

set(CMAKE_C_STANDARD 99)

file(GLOB PROJECT_C_FILES "src/*.c")

file(GLOB PROJECT_HEADER_FILES "inc/*.h")

include_directories(inc/)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(BoardGame ${PROJECT_C_FILES} ${PROJECT_HEADER_FILES})