//
// Created by loan on 10/10/2019.
//

#include "labyrinth.h"
#include "game.h"

#ifndef PROJET1_FILE_H
#define PROJET1_FILE_H

#define MAP_FOLDER_NAME "maps/"
#define MAP_NAME_SIZE_MAX 20
#define MAP_FILE_EXTENSION ".cfg"

#define SCORE_FOLDER_NAME "scores/"
#define SCORE_FILE_EXTENSION ".score"
#define SCORE_PSEUDO_SIZE 25
#define SCORE_NB_MAX 10

int saveMap(Map *m);
int readMap(Map *m, char *filename);
int saveScore(Map *m, Leaderboard *leaderboard);
int readScore(Map *m, Leaderboard *leaderboard);
int hasIllegalCharacters(char *str);



#endif //PROJET1_FILE_H
