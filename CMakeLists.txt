cmake_minimum_required(VERSION 3.14)
project(projet1 C)

set(CMAKE_C_STANDARD 99)

add_executable(projet1 src/main.c src/labyrinth.c includes/labyrinth.h src/display.c includes/display.h includes/minunit.h src/deck.c includes/deck.h src/file.c includes/file.h src/game.c includes/game.h src/monsters.c includes/monsters.h)