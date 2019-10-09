//
// Created by lalouache on 02/10/19.
//

#include <stdio.h>
#include <stdlib.h>
#include "includes/display.h"
#include "includes/labyrinthe.h"


void displayMatrix(int matrix[NB_LIG][NB_COL]) {
    for (int i = 0; i < NB_LIG; i++) {
        for (int j = 0; j < NB_COL; j++)
//            printf("%2d|", matrix[i][j]);
            if (matrix[i][j] == MUR)
                printf("#");
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


    return choice - 1;
}

void createMatrix(int *lig, int *col, int **matrix) {
    printf("=== Création d'un labyrinthe :\n");

    do {
        printf("\tLargeur (impair) : ");
        scanf("%d", col);
    } while (*col % 2 == 0 || col < 0);

    do {
        printf("\tHauteur (impair) : ");
        scanf("%d", lig);
    } while (*lig % 2 == 0 || lig < 0);

    matrix = malloc(*lig * sizeof(int));
    for (int i = 0; i < *lig; i++)
        (*matrix)[i] = malloc(*col * sizeof(int));
}