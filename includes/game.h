//
// Created by lalouache on 11/10/19.
//

#ifndef PROJET1_GAME_H
#define PROJET1_GAME_H

#include "labyrinthe.h"

#define TREASURE_VALUE 15
#define TRAP_VALUE 10

enum { OGRE, GHOST };
enum { NORTH, EAST, SOUTH, WEST };

typedef struct {
    Coordinate pos;
    int score;
    char *name;
} Player;

typedef struct Monster {
    Coordinate pos;
    int type;
} Monster;

typedef struct {
    Player *bestScores;
    int nbPlayer;
    int index;
} Leaderboard;

void play(Map *m);
int movePlayer(Map *m, Player *p, int direction);
void moveMonsters(Map *m);
void moveMonsterByType(Map *m, Monster *monster, int direction);
int getEligibleDirections(Map *m, Monster monster, int **tabDirections);
void testCase(Map *m, Player *p);
int comparePlayer(const Player *p1, const Player *p2);

#endif //PROJET1_GAME_H
