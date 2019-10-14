//
// Created by lalouache on 11/10/19.
//

#ifndef PROJET1_GAME_H
#define PROJET1_GAME_H

#include "labyrinthe.h"

#define TREASURE_VALUE 15
#define TRAP_VALUE 10

typedef struct {
    Coordinate pos;
    int score;
} Player;

void play(Map *m);
int movePlayer(Map *m, Player *p, int direction);
void testCase(Map *m, Player *p);

#endif //PROJET1_GAME_H
