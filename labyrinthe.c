//
// Created by lalouache on 02/10/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "includes/labyrinthe.h"
#include "includes/display.h"
#include "includes/deck.h"

/**
 * Generate a static size matrix
 * @param matrix
 */
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

/**
 * Generate path through the matrix
 * @param matrix
 */
void generatePath(int matrix[NB_LIG][NB_COL]) {
    Coordinate c;
    int nbBreakWalls = 0;
    srand(time(NULL));

    /* Matrix entrance */
    matrix[1][0] = 0;

    /* Matrix exit */
    matrix[NB_LIG - 2][NB_COL - 1] = 0;

    while (nbBreakWalls < (NB_LIG) * (NB_COL) - 1) {
        /* Pick a random case */
        c.lig = (1 + (rand() % (NB_LIG - 2))) | 1;
        c.col = (1 + (rand() % (NB_COL - 2))) | 1;

        /* Pick a random direction */
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

            displayMatrix(matrix);
            printf("==>%d\n", nbBreakWalls);
        }
    }
}

void generatePath2(int matrix[NB_LIG][NB_COL]) {
    Deck deck;
    deck.size = getWalls(matrix, &deck.walls);

    int nbBreakWall = 0;

    srand(time(NULL));
    while (nbBreakWall < (NB_LIG - 2) * (NB_COL - 2) - 1) {
        int wallIndex = rand() % deck.size;
        Coordinate wall = deckPick(wallIndex, &deck);


        int direction = rand() % 2;

        if (direction == VERTICAL) {
            if (breakWall2(matrix, wall, (Coordinate) {-1, 0})) nbBreakWall++;
            if (breakWall2(matrix, wall, (Coordinate) {+1, 0})) nbBreakWall++;
        } else {
            if (breakWall2(matrix, wall, (Coordinate) {0, -1})) nbBreakWall++;
            if (breakWall2(matrix, wall, (Coordinate) {0, +1})) nbBreakWall++;
        }

        nbBreakWall++;
    }

    printf("Broken walls : %d\nTotal walls : %d\n", nbBreakWall, (NB_LIG - 2) * (NB_COL - 2));
    displayMatrix(matrix);
}

int breakWall2(int matrix[NB_LIG][NB_COL], Coordinate cWall, Coordinate shift) {
/* Avoid breaking border walls */
    if (cWall.lig + shift.lig == 0 || cWall.lig + shift.lig == NB_LIG - 1 ||
        cWall.col + shift.col == 0 || cWall.col + shift.col == NB_COL - 1) {
        //printf("Can't break border %d;%d\n", cWall.lig, cWall.col);
        return 0;
    }


    /* Avoid breaking a wall having the same case value on the other side */
    if (matrix[cWall.lig + shift.lig][cWall.col + shift.col] == matrix[cWall.lig - shift.lig][cWall.col - shift.col]) {
        //printf("Can't break value %d\n", matrix[cWall.lig + shift.lig][cWall.col + shift.col]);
        return 0;
    }

    /* Breaking the wall */
    if (matrix[cWall.lig][cWall.col] == MUR) {
//        printf("Break : %d;%d ==> %d\n", cWall.lig, cWall.col, matrix[cCase.lig][cCase.col]);
        matrix[cWall.lig][cWall.col] = matrix[cWall.lig + shift.lig][cWall.col + shift.col];
        updateCase(matrix, cWall.lig, cWall.col, matrix[cWall.lig][cWall.col]);
        return 1;
    }

    return 0;
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
    if (cWall.lig == 0 || cWall.lig == NB_LIG - 1 || cWall.col == 0 || cWall.col == NB_COL - 1) {
        printf("Can't break border %d;%d\n", cWall.lig, cWall.col);
        return 0;
    }


    /* Avoid breaking a wall having the same case value on the other side */
    if (matrix[cWall.lig + shift.lig][cWall.col + shift.col] == matrix[cCase.lig][cCase.col]) {
        printf("Can't break value %d\n", matrix[cWall.lig + shift.lig][cWall.col + shift.col]);
        return 0;
    }

    /* Breaking the wall */
    if (matrix[cWall.lig][cWall.col] == MUR) {
        printf("Break : %d;%d ==> %d\n", cWall.lig, cWall.col, matrix[cCase.lig][cCase.col]);
        matrix[cWall.lig][cWall.col] = matrix[cCase.lig][cCase.col];
        updateCase(matrix, cWall.lig, cWall.col, matrix[cWall.lig][cWall.col]);
        return 1;
    }

    return 0;
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

    /* Update upper cases */
    if (lig - 1 > 0 && matrix[lig - 1][col] != matrix[lig][col])
        updateCase(matrix, lig - 1, col, value);

    /* Update lower cases */
    if (lig + 1 < NB_LIG - 2 && matrix[lig + 1][col] != matrix[lig][col])
        updateCase(matrix, lig + 1, col, value);

    /* Update left side cases */
    if (col - 1 > 0 && matrix[lig][col - 1] != matrix[lig][col])
        updateCase(matrix, lig, col - 1, value);

    /* Update right side cases */
    if (col + 1 < NB_COL - 1 && matrix[lig][col + 1] != matrix[lig][col])
        updateCase(matrix, lig, col + 1, value);
}

int getWalls(int matrix[NB_LIG][NB_COL], Coordinate **walls) {

    int nbWalls = 0;

    for (int i = 1; i < NB_LIG - 1; i++)
        for (int j = 1; j < NB_COL - 1; j++)
            if (matrix[i][j] == MUR)
                nbWalls++;


    (*walls) = malloc(nbWalls * sizeof(Coordinate));

    int indexWall = 0;
    for (int i = 1; i < NB_LIG - 1; i++)
        for (int j = 1; j < NB_COL - 1; j++)
            if (matrix[i][j] == MUR) {
                (*walls)[indexWall++] = (Coordinate) {i, j};
            }


    return nbWalls;
}
