cmake_minimum_required(VERSION 3.10)
project(BoardGame C)

set(CMAKE_C_STANDARD 99)

add_executable(BoardGame main.c gamehandler.c)