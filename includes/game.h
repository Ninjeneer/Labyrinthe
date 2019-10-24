//
// Created by lalouache on 11/10/19.
//

#ifndef PROJET1_GAME_H
#define PROJET1_GAME_H

#include "labyrinth.h"

#define TREASURE_VALUE 15
#define TRAP_VALUE 10
#define OGRE_TREASURE_DISTANCE 3

enum { OGRE, GHOST };
enum { NORTH, EAST, SOUTH, WEST };

typedef struct Player {
    Coordinate pos;
    Coordinate lastPos;
    int score;
    char *name;
} Player;

typedef struct Monster {
    Coordinate pos;
    Coordinate lastPos;
    Coordinate spawn;
    int radius;
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
void testCase(Map *m, Player *p, char message[255]);
int comparePlayer(const Player *p1, const Player *p2);
int comparePos(Coordinate c1, Coordinate c2);

#endif //PROJET1_GAME_H
