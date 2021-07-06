cmake_minimum_required(VERSION 3.19)
project(ciphers C)

set(CMAKE_C_STANDARD 11)

add_executable(ciphers vernam/main.c)