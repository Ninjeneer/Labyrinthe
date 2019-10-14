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
                return 0;

            default:
                printf("Unknown choice.");
                break;
        }
    }
}