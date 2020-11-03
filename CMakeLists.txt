cmake_minimum_required(VERSION 2.8.12.2)
project(coolServer C)

set(CMAKE_C_STANDARD 11)

add_executable(coolServer  main.c server.c handler.c utils.c)
