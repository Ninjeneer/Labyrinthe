//
// Created by lalouache on 02/10/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "labyrinthe.h"
#include "display.h"


void generateStaticMatrix(int matrix[NB_LIG][NB_COL]) {
    /* Matrix initialization and border wall construction */
    for (int i = 0; i < NB_LIG; i++)
        for (int j = 0; j < NB_COL; j++)
            if (i == 0 || i == NB_LIG - 1 || j == 0 || j == NB_COL - 1)
                matrix[i][j] = MUR;
            else
                matrix[i][j] = i * NB_LIG + j;

    /* Inner horizontal wall construction */
    for (int i = 2; i < NB_LIG; i += 2)
        for (int j = 0; j < NB_COL; j++)
            matrix[i][j] = MUR;

    /* Inner vertical wall construction */
    for (int i = 0; i < NB_LIG; i++)
        for (int j = 2; j < NB_COL; j += 2)
            matrix[i][j] = MUR;

}

void generatePath(int matrix[NB_LIG][NB_COL]) {
    Coordinate c;
    int nbBreakWalls = 0;
    srand(time(NULL));


    while (nbBreakWalls < (NB_LIG - 1) * (NB_COL - 1) - 1) {
        c.lig = (1 + (rand() % (NB_LIG - 2))) | 1;
        c.col = (1 + (rand() % (NB_COL - 2))) | 1;

        int direction = rand() % 4;

        Coordinate shift = {0, 0};

        switch (direction) {
            case NORTH:
                shift.lig = -1;
                break;
            case EAST:
                shift.col = +1;
                break;
            case WEST:
                shift.col = -1;
                break;
            case SOUTH:
                shift.lig = +1;
                break;
            default:
                break;
        }

        Coordinate cWall = {c.lig + shift.lig, c.col + shift.col};

//        printf("Direction : %d\n\tccase.lig = %d\tccase.col = %d\n\tcwall.lig = %d\tcwall.col = %d\n\tshift.lig = %d\tshift.col = %d", direction, c.lig, c.col, cWall.lig, cWall.col, shift.lig, shift.col);
//        getchar();
//
        if (breakWall(matrix, c, cWall, shift)) {
            nbBreakWalls++;
        }
    }
}

/**
 * Break a wall
 * @param matrix
 * @param cCase
 * @param cWall
 * @param shift
 * @return
 */
int breakWall(int matrix[NB_LIG][NB_COL], Coordinate cCase, Coordinate cWall, Coordinate shift) {
    /* Avoid breaking border walls */
    if (cWall.lig == 0 || cWall.lig == NB_LIG - 1 || cWall.col == 0 || cWall.col == NB_COL - 1)
        return 0;

    /* Avoid breaking a wall having the same case value on the other side */
    if (matrix[cWall.lig + shift.lig][cWall.col + shift.col] == matrix[cCase.lig][cCase.col])
        return 0;

    /* Breaking the wall */
    if (matrix[cWall.lig][cWall.col] == MUR) {
        matrix[cWall.lig][cWall.col] = matrix[cCase.lig][cCase.col];
        updateCase(matrix, cWall.lig, cWall.col, matrix[cWall.lig][cWall.col]);
        return 1;
    }
}

/**
 * Recursively update available cases
 * @param matrix
 * @param lig
 * @param col
 * @param value
 */
void updateCase(int matrix[NB_LIG][NB_COL], int lig, int col, int value) {
    if (matrix[lig][col] == MUR)
        return;

    matrix[lig][col] = value;

    if (lig - 1 > 0 && matrix[lig - 1][col] != matrix[lig][col])
        updateCase(matrix, lig - 1, col, value);

    if (lig + 1 < NB_LIG - 2 && matrix[lig + 1][col] != matrix[lig][col])
        updateCase(matrix, lig + 1, col, value);

    if (col - 1 > 0 && matrix[lig][col - 1] != matrix[lig][col])
        updateCase(matrix, lig, col - 1, value);

    if (col + 1 < NB_COL - 1 && matrix[lig][col + 1] != matrix[lig][col])
        updateCase(matrix, lig, col + 1, value);
}
