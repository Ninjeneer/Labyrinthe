//
// Created by loan on 10/10/2019.
//

#include <stdio.h>
#include <string.h>
#include <bits/types/FILE.h>
#include <stdlib.h>
#include "includes/file.h"

int saveMap(Map *m) {

    FILE* file = fopen(strcat(FOLDER_NAME, strcat(m->name, ".cfg")), "w+");

    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier : %s", m->name);
        return EXIT_FAILURE;
    }

    fprintf(file, "%s\n", m->name);
    fprintf(file, "%d %d\n", m->nbLig, m->nbCol);

    for (int i = 0; i < m->nbLig; i++) {
        for (int j = 0; j < m->nbCol; j++)
            fprintf(file, "%d ", m->matrix[i][j]);

        fprintf(file, "\n");
    }

    fclose(file);

    return EXIT_SUCCESS;
}