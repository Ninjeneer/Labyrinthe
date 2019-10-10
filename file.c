//
// Created by loan on 10/10/2019.
//

#include <stdio.h>
#include <string.h>
#include <bits/types/FILE.h>
#include <stdlib.h>
#include "includes/file.h"

/**
 * Save a map into a file
 * @param m  Map
 * @return  0 if fail, 1 if success
 */
int saveMap(Map *m) {

    char *filename = (char*)malloc((strlen(MAP_FOLDER_NAME) + strlen(m->name) + strlen(MAP_FILE_EXTENSION) * sizeof(char)));
    strcat(filename, MAP_FOLDER_NAME);
    strcat(filename, m->name);
    strcat(filename, MAP_FILE_EXTENSION);

    FILE* file = fopen(filename, "w+");

    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier : %s", m->name);
        return 0;
    }

    /* Write the map name */
    fprintf(file, "%s", m->name);
    /* Write the map's dimensions */
    fprintf(file, "%d %d\n", m->nbLig, m->nbCol);

    /* Write the map's matrix */
    for (int i = 0; i < m->nbLig; i++) {
        for (int j = 0; j < m->nbCol; j++)
            fprintf(file, "%d ", m->matrix[i][j]);

        fprintf(file, "\n");
    }

    fclose(file);

    return 1;
}