//
// Created by lalouache on 18/10/19.
//

#include "includes/monsters.h"

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
                monster->pos.lig++;
            break;

        case WEST:
            if (m->matrix[monster->pos.lig][monster->pos.col - 1] != WALL)
                monster->pos.lig--;
            break;

        default:
            break;
    }
}

void moveGhost(Map *m, Monster *monster, int direction) {
    switch (direction) {
        case NORTH:
            if (m->matrix[monster->pos.lig - 1][monster->pos.col] != WALL || (monster->pos.lig - 2 > 0 && m->matrix[monster->pos.lig - 2][monster->pos.col] != WALL))
                monster->pos.lig--;
            break;

        case SOUTH:
            if (m->matrix[monster->pos.lig + 1][monster->pos.col] != WALL || (monster->pos.lig + 2 < m->nbLig - 1 && m->matrix[monster->pos.lig + 2][monster->pos.col] != WALL))
                monster->pos.lig++;
            break;

        case EAST:
            if (m->matrix[monster->pos.lig][monster->pos.col + 1] != WALL || (monster->pos.col + 1 < m-> nbCol - 1 && m->matrix[monster->pos.lig][monster->pos.col + 2] != WALL))
                monster->pos.lig++;
            break;

        case WEST:
            if (m->matrix[monster->pos.lig][monster->pos.col - 1] != WALL || (monster->pos.col - 2 > 0 && m->matrix[monster->pos.lig][monster->pos.col - 2] != WALL))
                monster->pos.lig--;
            break;

        default:
            break;
    }
}

