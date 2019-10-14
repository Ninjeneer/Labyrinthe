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

/**
 * Display the game
 * @param m Map
 * @param p Player
 */
void displayGame(Map *m, Player p) {
    for (int i = 0; i < m->nbLig; i++) {
        for (int j = 0; j < m->nbCol; j++)
//            printf("%2d|", matrix[i][j]);
            if (m->matrix[i][j] == WALL)
                printf("#");
            else if (p.pos.lig == i && p.pos.col == j)
                printf("o");
            else if (m->matrix[i][j] == TREASURE)
                printf("T");
            else if (m->matrix[i][j] == TRAP)
                printf("P");
            else
                printf(" ");

        printf("\n");
    }
}

/**
 * Display the menu
 * @return User's choice
 */
int displayMenu() {
    printf("=== Labyrinthe ===\nMenu :\n\t1. Créer un labyrinthe\n\t2. Charger labyrinthe\n\t3. Jouer\n\t4. Quitter\n\n");

    int choice = 0;
    //TODO test valeur
    printf("Choix : ");
    while (scanf("%d", &choice) != 1) {
        printf("Choix : ");
    }

    clearBuffer();

    return choice - 1;
}

/**
 * Ask for map information, create it and save it
 * @param m Map
 */
void createMap(Map *m) {
    printf("=== Création d'un labyrinthe :\n");

    /* Ask for the width of the map */
    do {
        printf("\tLargeur (impair) : ");
        scanf("%d", &m->nbCol);
        clearBuffer();
    } while (m->nbCol % 2 == 0 || m->nbCol < 0);

    /* Ask for the height of the map */
    do {
        printf("\tHauteur (impair) : ");
        scanf("%d", &m->nbLig);
        clearBuffer();
    } while (m->nbLig % 2 == 0 || m->nbLig < 0);

    /* Create the matrix, generate the path */
    generateStaticMatrix(m);

    /* Ask for the name of the map */
    m->name = malloc(MAP_NAME_SIZE * sizeof(char));
    do {
        printf("Nom du labyrinthe (3 -> 20 car.): ");
        fgets(m->name, MAP_NAME_SIZE, stdin);
        fflush(stdin);
    } while (strlen(m->name) < 3 || strlen(m->name) > MAP_NAME_SIZE);

    m->name[strlen(m->name) - 1] = '\0'; /* Removes last \n */


    /* Save the map in a file */
    if (saveMap(m))
        printf("Labyrinthe enregistré et chargé avec succès.\n");
    else
        printf("Impossible de sauvegarder le labyrinthe.\n");
}

void openMap(Map *m) {
    /* Ask for the name of the map */
    m->name = malloc(MAP_NAME_SIZE * sizeof(char));
    do {
        printf("Nom du labyrinthe à ouvrir : ");
        fgets(m->name, MAP_NAME_SIZE, stdin);
        fflush(stdin);
    } while (strlen(m->name) < 3 || strlen(m->name) > MAP_NAME_SIZE);

    m->name[strlen(m->name) - 1] = '\0'; /* Removes last \n */

    if (readMap(m, m->name))
        printf("Labyrinthe chargé avec succès!\n");
    else
        printf("Erreur dans le chargement du labyrinthe !\n");
}


/**
 * Clear the stdin buffer
 */
void clearBuffer() {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void clearMap(Map *m) {
    if (m->name != NULL)
        free(m->name);

    if (m->matrix != NULL) {
        for (int i = 0; i < m->nbLig; i++)
            free(m->matrix[i]);

        free(m->matrix);
    }

    m->nbLig = 0;
    m->nbCol = 0;
}