/**
 * \file display.c
 * \brief Contains all the functions about display and user interaction.
 * \author Loan Alouache
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include "includes/display.h"
#include "includes/labyrinth.h"
#include "includes/file.h"
#include "includes/game.h"

/**
 * Display the game
 * @param m Map
 * @param p Player
 */
void displayGame(Map *m, Player p) {
    for (int i = 0; i < m->nbLig; i++) {
        for (int j = 0; j < m->nbCol; j++) {
            if (m->matrix[i][j] == WALL)
                printf("#");
            else if (p.pos.lig == i && p.pos.col == j)
                printf("o");
            else if (m->matrix[i][j] == TREASURE)
                printf("T");
            else if (m->matrix[i][j] == TRAP)
                printf("P");
            else if (m->difficulty == EASY || !displayMonsters(m, i, j))
                printf(" ");
        }

        printf("\n");
    }

    printf("Score : %d\n", p.score);
}

/**
 * Display a monster on a case
 * @param m Map
 * @param lig Current line displayed
 * @param col Current column displayed
 * @return 1 if a monster is displayed at lig;col position
 */
int displayMonsters(Map *m, int lig, int col) {
    int displayed = 0;
    for (int i = 0; i < m->nbMonsters; i++) {
        if (m->monsters[i].pos.lig == lig && m->monsters[i].pos.col == col) {
            displayed = 1;
            if (m->monsters[i].type == GHOST)
                printf("F");
            else if (m->monsters[i].type == OGRE)
                printf("O");
        }
    }

    return displayed;
}

/**
 * Display the menu
 * @return User's choice
 */
int displayMenu(Map m) {
    system("clear || cls");
    printf("████████╗██╗  ██╗███████╗    ██╗      █████╗ ██████╗ ██╗   ██╗██████╗ ██╗███╗   ██╗████████╗██╗  ██╗\n");
    printf("╚══██╔══╝██║  ██║██╔════╝    ██║     ██╔══██╗██╔══██╗╚██╗ ██╔╝██╔══██╗██║████╗  ██║╚══██╔══╝██║  ██║\n");
    printf("   ██║   ███████║█████╗      ██║     ███████║██████╔╝ ╚████╔╝ ██████╔╝██║██╔██╗ ██║   ██║   ███████║\n");
    printf("   ██║   ██╔══██║██╔══╝      ██║     ██╔══██║██╔══██╗  ╚██╔╝  ██╔══██╗██║██║╚██╗██║   ██║   ██╔══██║\n");
    printf("   ██║   ██║  ██║███████╗    ███████╗██║  ██║██████╔╝   ██║   ██║  ██║██║██║ ╚████║   ██║   ██║  ██║\n");
    printf("   ╚═╝   ╚═╝  ╚═╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚═════╝    ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═\n");

    printf("Menu :\n\t1. Créer un labyrinthe\n\t2. Charger labyrinthe\n\t3. Jouer\n\t4. Tableau des scores\n\t5. Quitter\n");

    int choice = 0;
    int maxChoice = (m.loaded) ? 5 : 4;

    //TODO test valeur
    printf("Choix : ");
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > maxChoice) {
        printf("Choix : ");
    }

    clearBuffer();

    return choice - 1;
}

/**
 * Ask for map information, create it, save it and load it
 * @param m Map
 */
void createMap(Map *m) {
    printf("=== Création d'un labyrinthe :\n");

    /* Ask for game difficulty */
    char difficulty;
    do {
        printf("Difficulté [F]acile / [D]ifficile : ");
        scanf("%c", &difficulty);
        clearBuffer();
    } while (toupper(difficulty) != 'F' && toupper(difficulty) != 'D');
    m->difficulty = (toupper(difficulty) == 'F') ? EASY : HARD;

    /* Ask for the width of the map */
    do {
        printf("\tLargeur (impair >= 3) : ");
        scanf("%d", &m->nbCol);
        clearBuffer();
    } while (m->nbCol % 2 == 0 || m->nbCol < 0 || m->nbCol < 3);

    /* Ask for the height of the map */
    do {
        printf("\tHauteur (impair >= 3) : ");
        scanf("%d", &m->nbLig);
        clearBuffer();
    } while (m->nbLig % 2 == 0 || m->nbLig < 0 || m->nbCol < 3);

    /* Create the matrix, generate the path */
    generateStaticMatrix(m);

    /* Ask for the name of the map */
    m->name = malloc(MAP_NAME_SIZE * sizeof(char));
    do {
        printf("Nom du labyrinthe (3 -> %d car.): ", MAP_NAME_SIZE);
        fgets(m->name, MAP_NAME_SIZE, stdin);
        fflush(stdin);
    } while (strlen(m->name) < 3 || strlen(m->name) > MAP_NAME_SIZE);

    m->name[strlen(m->name) - 1] = '\0'; /* Removes last \n */




    /* Save the map in a file */
    if (saveMap(m)) {
        printf("Labyrinthe enregistré et chargé avec succès.\n\n");
        m->loaded = 1;
    } else {
        m->loaded = 0;
    }

}

/**
 * Ask for map name and load it
 * @param m Map
 */
void openMap(Map *m) {
    /* Show maps list */

    if (!showFileList()) {
        printf("Aucune map n'est enregistrée\n");
        return;
    }

    /* Ask for the name of the map */
    m->name = malloc(MAP_NAME_SIZE * sizeof(char));
    do {
        printf("Nom du labyrinthe à ouvrir : ");
        fgets(m->name, MAP_NAME_SIZE, stdin);
        fflush(stdin);
    } while (strlen(m->name) < 3 || strlen(m->name) > MAP_NAME_SIZE);

    m->name[strlen(m->name) - 1] = '\0'; /* Removes last \n */

    if (readMap(m, m->name)) {
        printf("Labyrinthe chargé avec succès!\n\n");
        m->loaded = 1;

        if (m->difficulty == HARD)
            generateMonsters(m);
    } else {
        m->loaded = 0;
    }
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

/**
 * Display the map folder content
 */
int showFileList() {
    DIR *d;
    struct dirent *dir;
    int nbFile = 0;

    d = opendir(MAP_FOLDER_NAME);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
                nbFile++;
        }

        closedir(d);
    }

    if (nbFile == 0)
        return 0;

    printf("Liste des maps disponibles :\n");
    d = opendir(MAP_FOLDER_NAME);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
                printf("\t%s\n", dir->d_name);
        }

        closedir(d);
    }

    return 1;
}

/**
 * Ask for the player pseudo in case of saving his score
 * @param m Played map
 * @param p Player
 * @param leaderboard Maps's leaderboard
 * @param add 1 to add a new entry, 0 to replace a player score
 */
void askScore(Map *m, Player *p, Leaderboard *leaderboard, int add) {
    if (add)
        printf("Vous faites partie des %d premiers à jouer ce labyrinthe\n", SCORE_NB_MAX);
    else
        printf("Félicitation, vous faites partie du top %d des scores !\n", SCORE_NB_MAX);

    p->name = malloc(SCORE_PSEUDO_SIZE * sizeof(char));

    do {
        printf("Entrez votre pseudo (3 -> %d car.): ", SCORE_PSEUDO_SIZE);
        fgets(p->name, SCORE_PSEUDO_SIZE, stdin);
    } while (strlen(p->name) < 3 || strlen(p->name) > SCORE_PSEUDO_SIZE);
    p->name[strlen(p->name) - 1] = '\0'; /* Removes last \n */

    if (add)
        leaderboard->bestScores[leaderboard->nbPlayer++] = *p;
    else
        leaderboard->bestScores[leaderboard->nbPlayer - 1] = *p;


    saveScore(m, leaderboard);
}

/**
 * Display a specific leaderboard
 * @param m Leaderboard's map
 */
void showLeaderboard(Map m) {
    if (!m.loaded) {
        printf("Erreur : aucune map n'est chargée !\n");
        return;
    }

    Leaderboard l;
    readScore(&m, &l);

    printf("== Tableau des scores de : %s ==\n", m.name);
    for (int i = 0; i < l.nbPlayer; i++)
        printf("\t[%2d] => %s : %d\n", (i + 1), l.bestScores[i].name, l.bestScores[i].score);

    printf("\n");
}