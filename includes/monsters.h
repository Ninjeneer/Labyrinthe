//
// Created by lalouache on 18/10/19.
//

#include "labyrinth.h"
#include "game.h"

#ifndef PROJET1_MONSTERS_H
#define PROJET1_MONSTERS_H

void moveGhost(Map *m, Monster *monster, int direction);
void moveOgre(Map *m, Monster *monster, int direction);
int getEligibleDirections(Map *m, Monster monster, int **tabDirections);
void move(Map *m, Monster *monster, void (*moveFunction)(Map*, Monster*, int));

#endif //PROJET1_MONSTERS_H
