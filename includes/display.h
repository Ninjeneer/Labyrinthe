//
// Created by lalouache on 02/10/19.
//

#ifndef PROJET1_DISPLAY_H
#define PROJET1_DISPLAY_H

#include "labyrinthe.h"

enum { CREATE, OPEN, PLAY, QUIT};

void displayMatrix(int matrix[NB_LIG][NB_COL]);
int displayMenu();
void createMatrix(int *lig, int *col, int **matrix);


#endif //PROJET1_DISPLAY_H
