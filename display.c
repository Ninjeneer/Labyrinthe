//
// Created by lalouache on 02/10/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes/display.h"
#include "includes/labyrinthe.h"
#include "includes/file.h"
#include "includes/game.h"


void displayGame(Map *m, Player p) {
    for (int i = 0; i < m->nbLig; i++) {
        for (int j = 0; j < m->nbCol; j++)
//            printf("%2d|", matrix[i][j]);
            if (m->matrix[i][j] == MUR)
                printf("#");
            else if (p.pos.lig == i && p.pos.col == j)
                printf("o");
            else
                printf(" ");

        printf("\n");
    }
}

int displayMenu() {
    printf("=== Labyrinthe ===\nMenu :\n\t1. Créer un labyrinthe\n\t2. Charger labyrinthe\n\t3. Jouer\n\t4. Quitter\n\n");

    int choice = 0;

    printf("Choix : ");
    while (scanf("%d", &choice) != 1) {
        printf("Choix : ");
    }

    clearBuffer();

    return choice - 1;
}

void createMatrix(Map *m) {
    printf("=== Création d'un labyrinthe :\n");

    do {
        printf("\tLargeur (impair) : ");
        scanf("%d", &m->nbCol);
        clearBuffer();
    } while (m->nbCol % 2 == 0 || m->nbCol < 0);

    do {
        printf("\tHauteur (impair) : ");
        scanf("%d", &m->nbLig);
        clearBuffer();
    } while (m->nbLig % 2 == 0 || m->nbLig < 0);

    /* Create the matrix, generate the path */
    generateStaticMatrix(m);

    m->name = malloc(MAP_NAME_SIZE * sizeof(char));
    do {
        printf("Nom du labyrinthe (3 -> 20 car.): ");
        fgets(m->name, MAP_NAME_SIZE, stdin);
   } while (strlen(m->name) < 3 || strlen(m->name) > MAP_NAME_SIZE);

   m->name[strlen(m->name)-1] = '\0';


    if (saveMap(m))
        printf("Labyrinthe enregistré et chargé avec succès.\n");
    else
        printf("Impossible de sauvegarder le labyrinthe.\n");
}

void clearBuffer() {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}