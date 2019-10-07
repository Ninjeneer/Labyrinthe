//
// Created by lalouache on 02/10/19.
//

#ifndef PROJET1_LABYRINTHE_H
#define PROJET1_LABYRINTHE_H

#define NB_LIG 5
#define NB_COL 7

#define MUR -1

enum {NORTH, EAST, WEST, SOUTH};
enum {VERTICAL, HORIZONTAL};

typedef struct {
    int lig;
    int col;
} Coordinate;



void generateStaticMatrix(int matrix[NB_LIG][NB_COL]);
void generatePath(int matrix[NB_LIG][NB_COL]);
void generatePath2(int matrix[NB_LIG][NB_COL]);
int breakWall(int matrix[NB_LIG][NB_COL], Coordinate cCase, Coordinate cWall, Coordinate shift);
int breakWall2(int matrix[NB_LIG][NB_COL], Coordinate cWall, Coordinate shift);
void updateCase(int matrix[NB_LIG][NB_COL], int lig, int col, int value);
int getWalls(int matrix[NB_LIG][NB_COL], Coordinate **walls);

#endif //PROJET1_LABYRINTHE_H
