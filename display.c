//
// Created by lalouache on 02/10/19.
//

#include "display.h"
#include "labyrinthe.h"
#include <stdio.h>

void displayMatrix(int (*matrix)[23]) {
    for (int i = 0; i < NB_LIG; i++) {
        for (int j = 0; j < NB_COL; j++)
            printf("%d|", matrix[i][j]);

        printf("\n");
    }
}
