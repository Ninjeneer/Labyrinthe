/**
 * \file game.c
 * \brief Contains the main game functions and game logic.
 * \author Loan Alouache
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "includes/game.h"
#include "includes/labyrinth.h"
#include "includes/display.h"
#include "includes/file.h"
#include "includes/monsters.h"

/**
 * Start the game
 * @param m Map
 */
void play(Map *m) {
    if (m->loaded == 0) {
        printf("Erreur : aucune map n'est chargée !\n");
        pressAnyKey();
        return;
    }


    Player p;

    /* Place player at the begging of the map */
    p.pos = (Coordinate) {MATRIX_START_LIG, MATRIX_START_COL};

    /* Set default player score */
    p.score = m->nbLig * m->nbCol;

    /* Leaderboard initialization*/
    Leaderboard leaderboard;
    readScore(m, &leaderboard);

    /* User message */
    char message[MESSAGE_BUFFER_SIZE];
    strcpy(message, " ");

    /* Game loop */
    while (p.pos.lig != m->nbLig - 2 || p.pos.col != m->nbCol - 1) {
        displayGame(m, p, message);
        sprintf(message, " ");

        /* Ask for player direction */
        char direction = ' ';
        do {
            printf("Direction : ");
            scanf("%c", &direction);
            clearBuffer();
            direction = (char) toupper(direction);
        } while (direction != 'Z' && direction != 'Q' && direction != 'S' && direction != 'D');



        /* Try to move player */
        if (movePlayer(m, &p, direction)) {
            /* Decrease player score each step */
            p.score--;

            /* Move all the monsters */
            moveMonsters(m);

            /* Test objects */
            testCase(m, &p, message);
        }
    }

    sprintf(message, "/!\\ Bravo ! Vous êtes sorti du labyrinthe !");
    displayGame(m, p, message);

    /* If the number of registered scores is < SCORE_NB_MAX */
    if (leaderboard.nbPlayer < SCORE_NB_MAX) {
        askScore(m, &p, &leaderboard, 1);
    } else if (p.score > leaderboard.bestScores[leaderboard.nbPlayer - 1].score) {
        askScore(m, &p, &leaderboard, 0);
    }
}

/**
 * Try to move the player
 * @param m Map
 * @param p Player
 * @param direction wanted direction
 * @return 0 if fail, 1 if success
 */
int movePlayer(Map *m, Player *p, int direction) {
    switch (direction) {
        case 'Z':
            if (m->matrix[p->pos.lig - 1][p->pos.col] != WALL) {
                p->pos.lig--;
                return 1;
            }
            return 0;

        case 'Q':
            if (m->matrix[p->pos.lig][p->pos.col - 1] != WALL && p->pos.col - 1 >= 0) {
                p->pos.col--;
                return 1;
            }
            return 0;

        case 'S':
            if (m->matrix[p->pos.lig + 1][p->pos.col] != WALL) {
                p->pos.lig++;
                return 1;
            }
            return 0;

        case 'D':
            if (m->matrix[p->pos.lig][p->pos.col + 1] != WALL && p->pos.col + 1 < m->nbCol) {
                p->pos.col++;
                return 1;
            }
            return 0;

        default:
            return 0;
    }
}

/**
 * Move monsters on the map
 * @param m Map
 */
void moveMonsters(Map *m) {
    for (int i = 0; i < m->nbMonsters; i++) {
        if (m->monsters[i].type == OGRE)
            move(m, &m->monsters[i], &moveOgre);
        else if (m->monsters[i].type == GHOST)
            move(m, &m->monsters[i], &moveGhost);
    }
}


/**
 * Test whether the player is on an object or a monster
 * @param m Map
 * @param p Player
 */
void testCase(Map *m, Player *p, char message[255]) {
    if (m->matrix[p->pos.lig][p->pos.col] == TRAP) {
        p->score -= TRAP_VALUE;
        m->matrix[p->pos.lig][p->pos.col] = EMPTY;
        sprintf(message, "Vous êtes tombé dans un piège, vous perdez %d points !", TRAP_VALUE);
    } else if (m->matrix[p->pos.lig][p->pos.col] == TREASURE) {
        p->score += TREASURE_VALUE;
        m->matrix[p->pos.lig][p->pos.col] = EMPTY;
        //printf("Vous avez trouvé un trésor, vous gagnez %d points !\n", TREASURE_VALUE);
        sprintf(message, "Vous avez trouvé un trésor, vous gagnez %d points !", TREASURE_VALUE);
    }

    for (int i = 0; i < m->nbMonsters; i++) {
        Monster monster = m->monsters[i];
        if (p->pos.lig == monster.pos.lig && p->pos.col == monster.pos.col) {
            p->score -= MONSTER_VALUE;
            sprintf(message, "Vous avez été touché par un monstre ! Vous perdez %d points !", MONSTER_VALUE);
        }
    }
}

/**
 * Compare 2 players, useful in score sorting
 * @param p1 Player 1
 * @param p2 Player 2
 * @return 1 if player 1 has the highest score, -1 if player 1 has the lowest score, 0 if same
 */
int comparePlayer(const Player *p1, const Player *p2) {
    if (p1->score > p2->score)
        return -1;
    if (p1->score < p2->score)
        return 1;

    return 0;
}