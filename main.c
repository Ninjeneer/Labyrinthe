/**
 * \file main.c
 * \brief Game entry point.
 * \author Loan Alouache
 */

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "includes/labyrinth.h"
#include "includes/display.h"
#include "includes/game.h"
#include "includes/file.h"

int main() {

//    int error = 1;
//    int foo = 0;
//    do {
//        printf("lol : ");
//        error = scanf("%d", &foo);
//        clearBuffer();
//    } while (!error || foo < 0 || foo > 4);

    Map m;
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