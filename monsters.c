/**
 * \file monsters.c
 * \brief Contains all the functions allowing to move monsters.
 * \author Loan Alouache
 */

#include <stdlib.h>
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
    switch (direction) {
        case NORTH:
            if (m->matrix[monster->pos.lig - 1][monster->pos.col] != WALL)
                monster->pos.lig--;
            break;

        case SOUTH:
            if (m->matrix[monster->pos.lig + 1][monster->pos.col] != WALL)
                monster->pos.lig++;
            break;

        case EAST:
            if (m->matrix[monster->pos.lig][monster->pos.col + 1] != WALL)
                monster->pos.col++;
            break;

        case WEST:
            if (m->matrix[monster->pos.lig][monster->pos.col - 1] != WALL)
                monster->pos.col--;
            break;

        default:
            break;
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
            if (m->matrix[monster->pos.lig - 1][monster->pos.col] != WALL)
                monster->pos.lig--;
            else if (monster->pos.lig - 2 > 0 && m->matrix[monster->pos.lig - 2][monster->pos.col] == EMPTY)
                monster->pos.lig -= 2;
            break;

        case SOUTH:
            if (m->matrix[monster->pos.lig + 1][monster->pos.col] != WALL)
                monster->pos.lig++;
            else if (monster->pos.lig + 2 < m->nbLig - 1 && m->matrix[monster->pos.lig + 2][monster->pos.col] == EMPTY)
                monster->pos.lig += 2;
            break;

        case EAST:
            if (m->matrix[monster->pos.lig][monster->pos.col + 1] != WALL)
                monster->pos.col++;
            else if (monster->pos.col + 1 < m-> nbCol - 1 && m->matrix[monster->pos.lig][monster->pos.col + 2] == EMPTY)
                monster->pos.col += 2;
            break;

        case WEST:
            if (m->matrix[monster->pos.lig][monster->pos.col - 1] != WALL)
                monster->pos.col--;
            else if (monster->pos.col - 2 > 0 && m->matrix[monster->pos.lig][monster->pos.col - 2] == EMPTY)
                monster->pos.col -= 2;
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

