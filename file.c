/**
 * \file file.c
 * \brief Contains all the functions about manipulating files.
 * \author Loan Alouache
 */

#include <stdio.h>
#include <string.h>
#include <bits/types/FILE.h>
#include <stdlib.h>
#include "includes/file.h"
#include "includes/display.h"


/**
 * Save a map into a file
 * @param m Map
 * @return 0 if fail, 1 if success
 */
int saveMap(Map *m) {

    if (hasIllegalCharacters(m->name)) {
        printf("Erreur : nom de fichier invalide !\n");
        return 0;
    }

    /* Map file creation */
    char *filename = (char *) calloc((strlen(MAP_FOLDER_NAME) + strlen(m->name) + strlen(MAP_FILE_EXTENSION)),
                                     sizeof(char));
    strcat(filename, MAP_FOLDER_NAME);
    strcat(filename, m->name);
    strcat(filename, MAP_FILE_EXTENSION);

    FILE *file = fopen(filename, "w+");

    /* Test file existence */
    if (file == NULL) {
        printf("Impossible de créer le fichier de map : %s\n", filename);
        return 0;
    }

    /* Write the map name */
    fprintf(file, "%s\n", m->name);
    /* Write the map's dimensions */
    fprintf(file, "%d %d\n", m->nbLig, m->nbCol);

    /* Write the map's matrix */
    for (int i = 0; i < m->nbLig; i++) {
        for (int j = 0; j < m->nbCol; j++)
            fprintf(file, "%d ", m->matrix[i][j]);

        fprintf(file, "\n");
    }

    fprintf(file, "%d", m->difficulty);

    fclose(file);
    free(filename);

    /* Score file creation */
    char *scoreFilename = (char *) calloc((strlen(SCORE_FOLDER_NAME) + strlen(m->name) + strlen(SCORE_FILE_EXTENSION)),
                                          sizeof(char));
    strcat(scoreFilename, SCORE_FOLDER_NAME);
    strcat(scoreFilename, m->name);
    strcat(scoreFilename, SCORE_FILE_EXTENSION);

    FILE *scoreFile = fopen(scoreFilename, "w+");
    if (scoreFile == NULL) {
        printf("Impossible de créer le fichier de score : %s\n", scoreFilename);
        return 0;
    }
    fclose(scoreFile);

    return 1;
}

/**
 * Read a map file
 * @param m Map
 * @param filename path of the file
 * @return 0 if fail, 1 if success
 */
int readMap(Map *m, char *filename) {

    char *fullPath = (char *) calloc((strlen(MAP_FOLDER_NAME) + strlen(filename) + strlen(MAP_FILE_EXTENSION)),
                                     sizeof(char));
    strcat(fullPath, MAP_FOLDER_NAME);
    strcat(fullPath, filename);
    strcat(fullPath, MAP_FILE_EXTENSION);

    FILE *file = fopen(fullPath, "r");

    if (file == NULL) {
        printf("Impossible de lire le fichier : %s\n", fullPath);
        return 0;
    }

    fscanf(file, "%*s\n");
    fscanf(file, "%d %d\n", &m->nbLig, &m->nbCol);

    m->matrix = (int **) malloc(m->nbLig * sizeof(int *));
    for (int i = 0; i < m->nbLig; i++)
        m->matrix[i] = (int *) malloc(m->nbCol * sizeof(int));

    for (int i = 0; i < m->nbLig; i++) {
        for (int j = 0; j < m->nbCol; j++)
            fscanf(file, "%d ", &m->matrix[i][j]);

        fscanf(file, "\n");
    }

    fscanf(file, "%d", &m->difficulty);

    fclose(file);
    free(fullPath);

    return 1;
}

int saveScore(Map *m, Leaderboard *leaderboard) {

    char *filename = (char *) calloc((strlen(SCORE_FOLDER_NAME) + strlen(m->name) + strlen(SCORE_FILE_EXTENSION)),
                                     sizeof(char));
    strcat(filename, SCORE_FOLDER_NAME);
    strcat(filename, m->name);
    strcat(filename, SCORE_FILE_EXTENSION);

    FILE *file = fopen(filename, "w+");

    /* Test file existence */
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier de socre : %s\n", filename);
        return 0;
    }

    qsort(leaderboard->bestScores, leaderboard->nbPlayer, sizeof(Player), comparePlayer);

    for (int i = 0; i < leaderboard->nbPlayer; i++) {
        fprintf(file, "%s %d\n", leaderboard->bestScores[i].name, leaderboard->bestScores[i].score);
    }

    fclose(file);
    free(filename);

    return 1;
}

/**
 * Reads a score file
 * @param m Map
 * @param bestScores Array of players
 * @return 0 if fail reading, 1 if success
 */
int readScore(Map *m, Leaderboard *leaderboard) {

    char *filename = (char *) calloc((strlen(SCORE_FOLDER_NAME) + strlen(m->name) + strlen(SCORE_FILE_EXTENSION)),
                                     sizeof(char));
    strcat(filename, SCORE_FOLDER_NAME);
    strcat(filename, m->name);
    strcat(filename, SCORE_FILE_EXTENSION);

    FILE *file = fopen(filename, "r");

    /* Tests file existence */
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier de score : %s\n", filename);
        return 0;
    }

    /* Reads the number of saved scores */
    int nbEntry = 0;
    for (char c = getc(file); c != EOF; c = getc(file))
        if (c == '\n')
            nbEntry = nbEntry + 1;

    leaderboard->bestScores = (Player *) malloc(SCORE_NB_MAX * sizeof(Player));
    leaderboard->nbPlayer = nbEntry;

    if (nbEntry > 0) {

        /* Resets file cursor */
        fseek(file, 0, SEEK_SET);

        /* Reads the scores and fill the array */
        for (int i = 0; i < nbEntry; i++) {
            char buffer[SCORE_PSEUDO_SIZE] = {0};
            int s;
            fscanf(file, "%s %d\n", buffer, &s);

            /* Retrieves player name */
            leaderboard->bestScores[i].name = (char*)malloc(SCORE_PSEUDO_SIZE * sizeof(char));
            strcpy(leaderboard->bestScores[i].name, buffer);

            /* Retrieves player score */
            leaderboard->bestScores[i].score = s;
        }

        int (*pf)(const Player*, const Player*) = &comparePlayer;
        qsort(leaderboard->bestScores, leaderboard->nbPlayer, sizeof(Player), comparePlayer);
    }


    fclose(file);
    free(filename);

    return 1;
}

/**
 * Check if a string contains illegal characters
 * @param str string to test
 * @return 0 if string is clean
 */
int hasIllegalCharacters(char *str) {
    char illegalCharacters[] = "|/.\\~:";

    for (int i = 0; i < strlen(str); i++)
        for (int j = 0; j < strlen(illegalCharacters); j++)
            if (str[i] == illegalCharacters[j])
                return 1;

    return 0;
}