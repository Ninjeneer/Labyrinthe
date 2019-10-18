//
// Created by lalouache on 11/10/19.
//

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "includes/game.h"
#include "includes/labyrinthe.h"
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


    /* Game loop */
    while (p.pos.lig != m->nbLig - 2 || p.pos.col != m->nbCol - 1) {
        displayGame(m, p);

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

            /* Test objects */
            testCase(m, &p);

            /* Move all the monsters */
            moveMonsters(m);
        }
    }

    /* If the number of registered scores is < SCORE_NB_MAX */
    if (leaderboard.nbPlayer < SCORE_NB_MAX) {
        askScore(m, &p, &leaderboard, 1);
    } else if (p.score > leaderboard.bestScores[leaderboard.nbPlayer - 1].score) {
        askScore(m, &p, &leaderboard, 0);
    }

    printf("/!\\ Bravo ! Vous êtes sorti du labyrinthe, avec un score de %d !\n\n", p.score);
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
 * Test weither the player is on a treasure or on a trap and update score
 * @param m Map
 * @param p Player
 */
void testCase(Map *m, Player *p) {
    if (m->matrix[p->pos.lig][p->pos.col] == TRAP) {
        p->score -= TRAP_VALUE;
        m->matrix[p->pos.lig][p->pos.col] = EMPTY;
        printf("Vous êtes tombé dans un piège, vous perdez %d points !\n", TRAP_VALUE);
    } else if (m->matrix[p->pos.lig][p->pos.col] == TREASURE) {
        p->score += TREASURE_VALUE;
        m->matrix[p->pos.lig][p->pos.col] = EMPTY;
        printf("Vous avez trouvé un trésor, vous gagnez %d points !\n", TREASURE_VALUE);
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