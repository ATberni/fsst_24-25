cmake_minimum_required(VERSION 3.29)
project(battleship C)

set(CMAKE_C_STANDARD 23)

add_executable(battleship main.c console.c fsst.c)
