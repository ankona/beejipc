cmake_minimum_required(VERSION 3.13)
project(beej C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)

add_executable(beej main.c)