/** ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students. No portion of this
 * document may be reproduced, copied or revised without written
 * permission of the authors.

 * \file monsters.c
 * \brief Contains all the functions allowing to move monsters.
 * \author Loan Alouache
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../includes/monsters.h"

/**
 * Move any monster
 * @param m Map
 * @param monster Monster to move
 * @param moveFunction Callback to monster move function
 */
void move(Map *m, Monster *monster, void (*moveFunction)(Map *, Monster *, int)) {
    int *eligibleDirections;
    int nbDirections = getEligibleDirections(m, *monster, &eligibleDirections);
    int direction = eligibleDirections[rand() % nbDirections];

    moveFunction(m, monster, direction);
}

/**
 * Move an Orgre
 * @param m Map
 * @param monster Monster
 * @param direction direction to move
 */
void moveOgre(Map *m, Monster *monster, int direction) {
    Coordinate nextPos = monster->pos;
    switch (direction) {
        case NORTH:
            nextPos.row--;
            break;

        case SOUTH:
            nextPos.row++;
            break;

        case EAST:
            nextPos.col++;
            break;

        case WEST:
            nextPos.col--;
            break;

        default:
            break;
    }

    if (m->matrix[nextPos.row][nextPos.col] != WALL && canMoveRelativelyToSpawn(monster, nextPos)) {
        monster->lastPos = monster->pos;
        monster->pos = nextPos;

        if (m->matrix[monster->pos.row][monster->pos.col] == TREASURE) {
            monster->spawn = monster->pos;
            monster->radius = OGRE_TREASURE_DISTANCE;
        }
    }


}

/**
 * Move a ghost
 * @param m Map
 * @param monster Monster
 * @param direction direction to move
 */
void moveGhost(Map *m, Monster *monster, int direction) {
    int moveType = rand() % 2;

    Coordinate nextPos = monster->pos;

    switch (direction) {
        case NORTH:
            if (moveType == 0)
                nextPos.row--;
            else
                nextPos.row -= 2;
            break;

        case SOUTH:
            if (moveType == 0)
                nextPos.row++;
            else
                nextPos.row += 2;
            break;

        case EAST:
            if (moveType == 0)
                nextPos.col++;
            else
                nextPos.col += 2;
            break;

        case WEST:
            if (moveType == 0)
                nextPos.col--;
            else
                nextPos.col -= 2;
            break;

        default:
            break;
    }

    if (moveType == 0 && m->matrix[nextPos.row][nextPos.col] != WALL && canMoveRelativelyToSpawn(monster, nextPos)) {
        monster->lastPos = monster->pos;
        monster->pos = nextPos;
    } else if (moveType == 1 && nextPos.row > 0 && nextPos.row < m->nbRow - 1 && nextPos.col > 0 && nextPos.col < m->nbCol - 1 && m->matrix[nextPos.row][nextPos.col] != WALL && canMoveRelativelyToSpawn(monster, nextPos)) {
        monster->lastPos = monster->pos;
        monster->pos = nextPos;
    }
}

/**
 * Return the amount and an array of possible directions
 * @param m Map
 * @param monster Monster
 * @param tabDirections Array of eligible directions
 * @return number of eligible directions
 */
int getEligibleDirections(Map *m, Monster monster, int **tabDirections) {
    int nbDirections = 0;

    if (m->matrix[monster.pos.row - 1][monster.pos.col] != WALL || monster.type == GHOST)
        nbDirections++;
    if (m->matrix[monster.pos.row + 1][monster.pos.col] != WALL || monster.type == GHOST)
        nbDirections++;
    if (m->matrix[monster.pos.row][monster.pos.col - 1] != WALL || monster.type == GHOST)
        nbDirections++;
    if (m->matrix[monster.pos.row][monster.pos.col + 1] != WALL || monster.type == GHOST)
        nbDirections++;

    (*tabDirections) = (int *) calloc(nbDirections, sizeof(int));
    int index = 0;

    if (m->matrix[monster.pos.row - 1][monster.pos.col] != WALL || monster.type == GHOST)
        (*tabDirections)[index++] = NORTH;
    if (m->matrix[monster.pos.row + 1][monster.pos.col] != WALL || monster.type == GHOST)
        (*tabDirections)[index++] = SOUTH;
    if (m->matrix[monster.pos.row][monster.pos.col - 1] != WALL || monster.type == GHOST)
        (*tabDirections)[index++] = WEST;
    if (m->matrix[monster.pos.row][monster.pos.col + 1] != WALL || monster.type == GHOST)
        (*tabDirections)[index++] = EAST;

    return nbDirections;
}

/**
 * Return the distance between 2 coordinates
 * @param c1
 * @param c2
 * @return
 */
int calcDistance(Coordinate c1, Coordinate c2) {
    return (int) (sqrt(pow(c1.col - c2.col, 2) + pow(c1.row - c2.row, 2)));
}

/**
 * Stick to a treasure if the ogre found it
 * @param monster Ogre
 * @param nextPos Future ogre position
 * @return 1 if can move, 0 if can't
 */
int canMoveRelativelyToSpawn(Monster *monster, Coordinate nextPos) {
    /* A treasure as already been found */
    if (calcDistance(nextPos, monster->spawn) <= monster->radius)
        return 1;
    return 0;
}

