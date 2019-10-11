//
// Created by lalouache on 11/10/19.
//

#ifndef PROJET1_GAME_H
#define PROJET1_GAME_H

#include "labyrinthe.h"

typedef struct {
    Coordinate pos;
} Player;

void play(Map *m);
void movePlayer(Map *m, Player *p, int direction);

#endif //PROJET1_GAME_H
