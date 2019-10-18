//
// Created by lalouache on 02/10/19.
//

#ifndef PROJET1_LABYRINTHE_H
#define PROJET1_LABYRINTHE_H


enum {WALL, EMPTY, TREASURE, TRAP};
enum {EASY, HARD};

#define MATRIX_START_LIG 1
#define MATRIX_START_COL 0

#define OBJECT_RATE 0.02

typedef struct {
    int lig;
    int col;
} Coordinate;

typedef struct {
    char *name;
    int **matrix;
    int nbLig;
    int nbCol;
    int loaded;
    int difficulty;
    struct Monster *monsters; /* Forward declaration */
    int nbMonsters;
} Map;



void generateStaticMatrix(Map *m);
void generatePath(Map *m);
int breakWall(Map *m, Coordinate cWall, Coordinate shift);
void updateCase(Map *m, int lig, int col, int value, int override);
int getWalls(Map *m, Coordinate **walls);
void generateObjects(Map *m);
void generateMonsters(Map *m);

#endif //PROJET1_LABYRINTHE_H
