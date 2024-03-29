/** ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students. No portion of this
 * document may be reproduced, copied or revised without written
 * permission of the authors.

 * \file main.c
 * \brief Game entry point.
 * \author Loan Alouache
 */

#include <stdio.h>
#include <stdbool.h>
#include "../includes/display.h"
#include "../includes/game.h"

int main() {

    Map m;
    m.nbMonsters = 0;
    m.loaded = false;

    while (true) {
        int playerChoice = displayMenu(m);

        switch (playerChoice) {
            case CREATE:
                createMap(&m);
                break;

            case OPEN:
                openMap(&m);
                break;

            case PLAY:
                play(&m);
                break;

            case LEADERBOARD:
                showLeaderboard(m);
                break;

            case QUIT:
                printf("Au revoir !\n");
                return 0;

            default:
                printf("Choix inconnu\n");
                break;
        }
    }
}