#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "includes/labyrinthe.h"
#include "includes/display.h"
#include "includes/game.h"

int main() {

    Map m;

    while (true) {
        int playerChoice = displayMenu();

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

            case QUIT:
                printf("Au revoir !\n");
                return 0;

            default:
                printf("Choix inconnu\n");
                break;
        }
    }
}