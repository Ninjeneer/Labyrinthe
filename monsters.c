/**
 * \file monsters.c
 * \brief Contains all the functions allowing to move monsters.
 * \author Loan Alouache
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "includes/monsters.h"

/**
 * Move any monster
 * @param m Map
 * @param monster Monster to move
 * @param moveFunction Callback to monster move function
 */
void move(Map *m, Monster *monster, void (*moveFunction)(Map*, Monster*, int)) {
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
            nextPos.lig--;
            break;

        case SOUTH:
            nextPos.lig++;
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

    if (m->matrix[nextPos.lig][nextPos.col] != WALL && canMoveRelativelyToTreasure(monster, nextPos)) {
        monster->lastPos = monster->pos;
        monster->pos = nextPos;

        if (m->matrix[monster->pos.lig][monster->pos.col] == TREASURE)
            monster->treasureSeen = monster->pos;
    }


}

/**
 * Move a ghost
 * @param m Map
 * @param monster Monster
 * @param direction direction to move
 */
void moveGhost(Map *m, Monster *monster, int direction) {
    switch (direction) {
        case NORTH:
            if (m->matrix[monster->pos.lig - 1][monster->pos.col] != WALL) {
                monster->lastPos = monster->pos;
                monster->pos.lig--;
            }
            else if (monster->pos.lig - 2 > 0 && m->matrix[monster->pos.lig - 2][monster->pos.col] == EMPTY) {
                monster->lastPos = monster->pos;
                monster->pos.lig -= 2;
            }
            break;

        case SOUTH:
            if (m->matrix[monster->pos.lig + 1][monster->pos.col] != WALL) {
                monster->lastPos = monster->pos;
                monster->pos.lig++;
            }

            else if (monster->pos.lig + 2 < m->nbLig - 1 && m->matrix[monster->pos.lig + 2][monster->pos.col] == EMPTY) {
                monster->lastPos = monster->pos;
                monster->pos.lig += 2;
            }
            break;

        case EAST:
            if (m->matrix[monster->pos.lig][monster->pos.col + 1] != WALL) {
                monster->lastPos = monster->pos;
                monster->pos.col++;
            }
            else if (monster->pos.col + 1 < m-> nbCol - 1 && m->matrix[monster->pos.lig][monster->pos.col + 2] == EMPTY) {
                monster->lastPos = monster->pos;
                monster->pos.col += 2;
            }
            break;

        case WEST:
            if (m->matrix[monster->pos.lig][monster->pos.col - 1] != WALL) {
                monster->lastPos = monster->pos;
                monster->pos.col--;
            }
            else if (monster->pos.col - 2 > 0 && m->matrix[monster->pos.lig][monster->pos.col - 2] == EMPTY) {
                monster->lastPos = monster->pos;
                monster->pos.col -= 2;
            }
            break;

        default:
            break;
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

    if (m->matrix[monster.pos.lig - 1][monster.pos.col] != WALL || monster.type == GHOST)
        nbDirections++;
    if (m->matrix[monster.pos.lig + 1][monster.pos.col] != WALL || monster.type == GHOST)
        nbDirections++;
    if (m->matrix[monster.pos.lig][monster.pos.col - 1] != WALL || monster.type == GHOST)
        nbDirections++;
    if (m->matrix[monster.pos.lig][monster.pos.col + 1] != WALL || monster.type == GHOST)
        nbDirections++;

    (*tabDirections) = (int *) calloc(nbDirections, sizeof(int));
    int index = 0;

    if (m->matrix[monster.pos.lig - 1][monster.pos.col] != WALL || monster.type == GHOST)
        (*tabDirections)[index++] = NORTH;
    if (m->matrix[monster.pos.lig + 1][monster.pos.col] != WALL || monster.type == GHOST)
        (*tabDirections)[index++] = SOUTH;
    if (m->matrix[monster.pos.lig][monster.pos.col - 1] != WALL || monster.type == GHOST)
        (*tabDirections)[index++] = WEST;
    if (m->matrix[monster.pos.lig][monster.pos.col + 1] != WALL || monster.type == GHOST)
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
    return (int)(sqrt( pow(c1.col - c2.col, 2) + pow(c1.lig - c2.lig, 2) ));
}

/**
 * Stick to a treasure if the ogre found it
 * @param monster Ogre
 * @param nextPos Future ogre position
 * @return 1 if can move, 0 if can't
 */
int canMoveRelativelyToTreasure(Monster *monster, Coordinate nextPos) {
    /* A treasure as already been found */
    if (comparePos(monster->treasureSeen, (Coordinate){-1, -1}) != 1) {
//        printf("Found treasure ! Sticking to %d;%d ==> (%d)\n", monster->treasureSeen.lig, monster->treasureSeen.col, calcDistance(monster->pos, monster->treasureSeen));
        if (calcDistance(nextPos, monster->treasureSeen) < OGRE_TREASURE_DISTANCE)
            return 1;
        return 0;
    }

    /* Treasure not yet found, can walk freely */
    return 1;
}

