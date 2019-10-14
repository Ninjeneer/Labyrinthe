//
// Created by loan on 10/10/2019.
//

#include "labyrinthe.h"

#ifndef PROJET1_FILE_H
#define PROJET1_FILE_H

#define MAP_FOLDER_NAME "maps/"
#define MAP_NAME_SIZE 20
#define MAP_FILE_EXTENSION ".cfg"

int saveMap(Map *m);
int readMap(Map *m, char *filename);

#endif //PROJET1_FILE_H
