#include <stdio.h>
#include <stdbool.h>
#include "includes/labyrinthe.h"
#include "includes/display.h"

int main() {

    Map m;

    int nbLig = 0, nbCol = 0;

    while (true) {
        int playerChoice = displayMenu();
        switch (playerChoice) {
            case CREATE:
                createMatrix(&m);
                break;

            case OPEN:
                break;

            case PLAY:
                break;

            case QUIT:
                return 0;

            default:
                printf("Unknown choice.");
                break;
        }
    }

    return 0;
}