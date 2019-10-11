//
// Created by lalouache on 02/10/19.
//

#ifndef PROJET1_DISPLAY_H
#define PROJET1_DISPLAY_H

#include "labyrinthe.h"
#include "game.h"

enum { CREATE, OPEN, PLAY, QUIT};

void displayGame(Map *m, Player p);
int displayMenu();
void createMatrix(Map *m);
void clearBuffer();


#endif //PROJET1_DISPLAY_H
