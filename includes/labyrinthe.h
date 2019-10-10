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
enum {VERTICAL, HORIZONTAL};

typedef struct {
    int lig;
    int col;
} Coordinate;

typedef struct {
    char *name;
    int **matrix;
    int nbLig;
    int nbCol;
} Map;



void generateStaticMatrix(Map *m);
void generatePath(Map *m);
int breakWall(Map *m, Coordinate cWall, Coordinate shift);
void updateCase(Map *m, int lig, int col, int value, int override);
int getWalls(Map *m, Coordinate **walls);

#endif //PROJET1_LABYRINTHE_H
