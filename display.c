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

/**
 * Display the game
 * @param m Map
 * @param p Player
 */
void displayGame(Map *m, Player p, const char message[MESSAGE_BUFFER_SIZE]) {
    displayTitle();
    printf("\n\n");

    for (int i = 0; i < m->nbRow; i++) {
        printf("\t");
        for (int j = 0; j < m->nbCol; j++) {
            if (m->matrix[i][j] == WALL)
                printf("█");
            else if (p.pos.row == i && p.pos.col == j) {
                printf(BLUE);
                printf("o");
            } else if (m->matrix[i][j] == TREASURE) {
                printf(YELLOW);
                printf("T");
            } else if (m->matrix[i][j] == TRAP) {
                printf(RED);
                printf("P");
            } else if (m->difficulty == EASY || !displayMonsters(m, i, j))
                printf(" ");


            printf(RESET);
        }


        printf("\n");
    }
    printf("%s\n", message);
    printf("\n\nScore : %d\n", p.score);
}

/**
 * Display a monster on a case
 * @param m Map
 * @param lig Current line displayed
 * @param col Current column displayed
 * @return 1 if a monster is displayed at lig;col position
 */
int displayMonsters(Map *m, int lig, int col) {
    for (int i = 0; i < m->nbMonsters; i++) {
        if (m->monsters[i].pos.row == lig && m->monsters[i].pos.col == col) {
            if (m->monsters[i].type == GHOST) {
                printf(MAGENTA);
                printf("F");
            } else if (m->monsters[i].type == OGRE) {
                printf(GREEN);
                printf("O");
            }

            return 1;
        }
    }

    return 0;
}

/**
 * Clear the console and print the game title
 */
void displayTitle() {
    system("clear || cls");
    printf("\n");
    printf(" ████████╗██╗  ██╗███████╗    ██╗      █████╗ ██████╗ ██╗   ██╗██████╗ ██╗███╗   ██╗████████╗██╗  ██╗\n");
    printf(" ╚══██╔══╝██║  ██║██╔════╝    ██║     ██╔══██╗██╔══██╗╚██╗ ██╔╝██╔══██╗██║████╗  ██║╚══██╔══╝██║  ██║\n");
    printf("    ██║   ███████║█████╗      ██║     ███████║██████╔╝ ╚████╔╝ ██████╔╝██║██╔██╗ ██║   ██║   ███████║\n");
    printf("    ██║   ██╔══██║██╔══╝      ██║     ██╔══██║██╔══██╗  ╚██╔╝  ██╔══██╗██║██║╚██╗██║   ██║   ██╔══██║\n");
    printf("    ██║   ██║  ██║███████╗    ███████╗██║  ██║██████╔╝   ██║   ██║  ██║██║██║ ╚████║   ██║   ██║  ██║\n");
    printf("    ╚═╝   ╚═╝  ╚═╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚═════╝    ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝\n");
}

/**
 * Display the menu
 * @return User's choice
 */
int displayMenu() {

    displayTitle();
    printf("Menu :\n\t1. Créer un labyrinthe\n\t2. Charger labyrinthe\n\t3. Jouer\n\t4. Tableau des scores\n\t5. Quitter\n");

    int choice = 0;

    int valid = 1;
    do {
        printf("Choix : ");
        valid = scanf("%d", &choice);
        if (!valid)
            clearBuffer();
    } while (!valid || choice < 1 || choice > 5);

    clearBuffer();

    return choice - 1;
}

/**
 * Ask for map information, create it, save it and load it
 * @param m Map
 */
void createMap(Map *m) {
    printf("► Création d'un labyrinthe :\n");

    int validInput = 1;

    /* Ask for game difficulty */
    char difficulty;
    do {
        printf("\tDifficulté [F]acile / [D]ifficile : ");
        validInput = scanf("%c", &difficulty);
        clearBuffer();
    } while (!validInput || (toupper(difficulty) != 'F' && toupper(difficulty) != 'D'));
    m->difficulty = (toupper(difficulty) == 'F') ? EASY : HARD;

    validInput = 1;
    /* Ask for the width of the map */
    do {
        printf("\tLargeur (impair >= 3) : ");
        validInput = scanf("%d", &m->nbCol);
        clearBuffer();
    } while (!validInput || m->nbCol % 2 == 0 || m->nbCol < 0 || m->nbCol < 3);

    validInput = 1;
    /* Ask for the height of the map */
    do {
        printf("\tHauteur (impair >= 3) : ");
        validInput = scanf("%d", &m->nbRow);
        clearBuffer();
    } while (!validInput || m->nbRow % 2 == 0 || m->nbRow < 0 || m->nbCol < 3);

    /* Create the matrix, generate the path */
    generateStaticMatrix(m);

    /* Ask for the name of the map */
    m->name = malloc(MAP_NAME_SIZE_MAX * sizeof(char));
    do {
        printf("Nom du labyrinthe (2 -> %d car.): ", MAP_NAME_SIZE_MAX);
        fgets(m->name, MAP_NAME_SIZE_MAX, stdin);
        fflush(stdin);
    } while (strlen(m->name) < 3 || strlen(m->name) > MAP_NAME_SIZE_MAX);

    m->name[strlen(m->name) - 1] = '\0'; /* Removes last \n */


    /* Save the map in a file */
    if (saveMap(m)) {
        printf("Labyrinthe enregistré et chargé avec succès.\n\n");
        pressAnyKey();
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
        printf("Aucune map n'est enregistrée !\n");
        pressAnyKey();
        return;
    }

    /* Ask for the name of the map */
    m->name = malloc(MAP_NAME_SIZE_MAX * sizeof(char));
    do {
        printf("Nom du labyrinthe à ouvrir : ");
        fgets(m->name, MAP_NAME_SIZE_MAX, stdin);
        fflush(stdin);
    } while (strlen(m->name) < 3 || strlen(m->name) > MAP_NAME_SIZE_MAX);

    m->name[strlen(m->name) - 1] = '\0'; /* Removes last \n */

    if (readMap(m, m->name)) {
        printf("Labyrinthe chargé avec succès!\n\n");
        pressAnyKey();
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
        printf("Entrez votre pseudo (2 -> %d car.): ", SCORE_PSEUDO_SIZE);
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
        pressAnyKey();
        return;
    }

    Leaderboard l;
    readScore(&m, &l);

    displayTitle();
    printf("\n\n╠══ Tableau des scores de : %s ══╣\n", m.name);
    for (int i = 0; i < l.nbPlayer; i++)
        printf("\t[%2d] → %s : %d points\n", (i + 1), l.bestScores[i].name, l.bestScores[i].score);

    printf("\n");
    pressAnyKey();
}

void pressAnyKey() {
    printf("Appuyez sur ENTRÉE pour revenir au menu...");
    getchar();
}