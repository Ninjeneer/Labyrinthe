#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "includes/labyrinthe.h"
#include "includes/display.h"
#include "includes/game.h"
#include "includes/file.h"

int main() {

    Map m;
    m.loaded = false;

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

//    Map m;
//    m.name = "testscore";
//
//    Player p;
//    p.score = 150;
//
//    Leaderboard l;
//    readScore(&m, &l);
//
//
//    askScore(&m, &p, &l);

//    Leaderboard l;
//    readScore(&m, &l);
//
//    printf("%s %d", l.bestScores[0].name, l.bestScores[0].score);
//
//    saveScore(&m, &l);
}