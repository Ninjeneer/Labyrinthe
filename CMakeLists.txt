cmake_minimum_required(VERSION 3.14)
project(projet1 C)

set(CMAKE_C_STANDARD 99)

add_executable(projet1 main.c labyrinthe.c labyrinthe.h display.c display.h)