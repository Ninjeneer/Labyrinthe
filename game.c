//
// Created by lalouache on 11/10/19.
//

#include <stdio.h>
#include <ctype.h>
#include "includes/game.h"
#include "includes/labyrinthe.h"
#include "includes/display.h"


void play(Map *m) {
    Player p;

    p.pos = (Coordinate) {MATRIX_START_LIG, MATRIX_START_COL};

    while (p.pos.lig != m->nbLig - 2 || p.pos.col != m->nbCol - 1) {
        displayGame(m, p);

        char direction = ' ';
        do {
            printf("Direction : ");
            scanf("%c", &direction);
            clearBuffer();
            direction = (char) toupper(direction);
        } while (direction != 'Z' && direction != 'Q' && direction != 'S' && direction != 'D');

        movePlayer(m, &p, direction);
    }

    printf("/!\\ Bravo ! Vous êtes sorti du labyrinthe !\n");
}

void movePlayer(Map *m, Player *p, int direction) {
    switch (direction) {
        case 'Z':
            if (m->matrix[p->pos.lig - 1][p->pos.col] != MUR)
                p->pos.lig--;
            break;

        case 'Q':
            if (m->matrix[p->pos.lig][p->pos.col - 1] != MUR && p->pos.col - 1 >= 0)
                p->pos.col--;
            break;

        case 'S':
            if (m->matrix[p->pos.lig + 1][p->pos.col] != MUR)
                p->pos.lig++;
            break;

        case 'D':
            if (m->matrix[p->pos.lig][p->pos.col + 1] != MUR && p->pos.col + 1 < m->nbCol)
                p->pos.col++;
            break;

        default:
            break;
    }
}