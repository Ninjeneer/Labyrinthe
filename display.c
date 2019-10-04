//
// Created by lalouache on 02/10/19.
//

#include "display.h"
#include "labyrinthe.h"
#include <stdio.h>

void displayMatrix(int matrix[NB_LIG][NB_COL]) {
    for (int i = 0; i < NB_LIG; i++) {
        for (int j = 0; j < NB_COL; j++)
            if (matrix[i][j] == MUR)
                printf("#");
            else
                printf(" ");

        printf("\n");
    }
}
