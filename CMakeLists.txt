cmake_minimum_required(VERSION 3.14)
project(projet1 C)

set(CMAKE_C_STANDARD 99)

add_executable(projet1 main.c labyrinthe.c includes/labyrinthe.h display.c includes/display.h includes/minunit.h deck.c includes/deck.h file.c includes/file.h game.c includes/game.h)