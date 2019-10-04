//
// Created by lalouache on 02/10/19.
//

#ifndef PROJET1_LABYRINTHE_H
#define PROJET1_LABYRINTHE_H

#define NB_LIG 9
#define NB_COL 23

#define VIDE 0
#define MUR -1

enum {NORTH, EAST, WEST, SOUTH};

typedef struct {
    int lig;
    int col;
} Coordinate;

void generateStaticMatrix(int matrix[NB_LIG][NB_COL]);
void generatePath(int matrix[NB_LIG][NB_COL]);
int breakWall(int matrix[NB_LIG][NB_COL], Coordinate cCase, Coordinate cWall, Coordinate shift);
void updateCase(int matrix[NB_LIG][NB_COL], int lig, int col, int value);

#endif //PROJET1_LABYRINTHE_H
