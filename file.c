//
// Created by loan on 10/10/2019.
//

#include <stdio.h>
#include <string.h>
#include <bits/types/FILE.h>
#include <stdlib.h>
#include "includes/file.h"
#include "includes/display.h"



/**
 * Save a map into a file
 * @param m  Map
 * @return  0 if fail, 1 if success
 */
int saveMap(Map *m) {

    char *filename = (char *) calloc((strlen(MAP_FOLDER_NAME) + strlen(m->name) + strlen(MAP_FILE_EXTENSION)), sizeof(char));
    strcat(filename, MAP_FOLDER_NAME);
    strcat(filename, m->name);
    strcat(filename, MAP_FILE_EXTENSION);

    FILE *file = fopen(filename, "w+");

    /* Test file existence */
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier : %s\n", filename);
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

    fclose(file);
    free(filename);

    return 1;
}

/**
 * Read a map file
 * @param m Map
 * @param filename path of the file
 * @return 0 if fail, 1 if success
 */
int readMap(Map *m, char *filename) {

    char *fullPath = (char *) calloc((strlen(MAP_FOLDER_NAME) + strlen(filename) + strlen(MAP_FILE_EXTENSION)), sizeof(char));
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

    fclose(file);
    free(fullPath);

    return 1;
}

int saveScore(Map *m, Player *p) {

    char *filename = (char *) calloc((strlen(SCORE_FOLDER_NAME) + strlen(m->name) + strlen(SCORE_FILE_EXTENSION)), sizeof(char));
    strcat(filename, SCORE_FOLDER_NAME);
    strcat(filename, m->name);
    strcat(filename, SCORE_FILE_EXTENSION);

    FILE *file = fopen(filename, "w+");

    /* Test file existence */
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier de socre : %s\n", filename);
        return 0;
    }

    /* Write the map name */
    fprintf(file, "%s\n", m->name);
    /* Write the map's dimensions */
    fprintf(file, "%d %d\n", m->nbLig, m->nbCol);

    fclose(file);
    free(filename);

    return 1;
}

int readScore(Map *m) {

    char *filename = (char *) calloc((strlen(SCORE_FOLDER_NAME) + strlen(m->name) + strlen(SCORE_FILE_EXTENSION)), sizeof(char));
    strcat(filename, SCORE_FOLDER_NAME);
    strcat(filename, m->name);
    strcat(filename, SCORE_FILE_EXTENSION);

    FILE *file = fopen(filename, "r");

    /* Test file existence */
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier de socre : %s\n", filename);
        return 0;
    }

    Player bestScores[SCORE_NB_BY_FILE];
    for (int i = 0; i < SCORE_NB_BY_FILE; i++) {
        fscanf(file, "%s %d", bestScores[i].name, &bestScores[i].score);
    }

    fclose(file);
    free(filename);

    return 1;
}