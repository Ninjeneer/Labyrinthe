//
// Created by lalouache on 02/10/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
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

void generatePath2(int matrix[NB_LIG][NB_COL]) {
    Deck deck;
    deck.size = getWalls(matrix, &deck.walls);


    deckDisplay(deck);
    int nbBreakWall = 0;
    int nbMaxWall = deck.size;

    srand(time(NULL));
    while (nbBreakWall < (NB_LIG / 2) * (NB_COL / 2) - 1) {
        int wallIndex = rand() % deck.size;
        Coordinate wall = deckPick(wallIndex, &deck);

        if (wall.lig % 2 != 0 && wall.col % 2 == 0) {
            if (breakWall2(matrix, wall, (Coordinate) {0, -1})) {
                deckRemove(wallIndex, &deck);
                nbBreakWall++;
            }
            if (breakWall2(matrix, wall, (Coordinate) {0, +1})) {
                deckRemove(wallIndex, &deck);
                nbBreakWall++;
            }
        } else if (wall.lig % 2 == 0 && wall.col % 2 != 0) {
            if (breakWall2(matrix, wall, (Coordinate) {-1, 0})) {
                deckRemove(wallIndex, &deck);
                nbBreakWall++;
            }
            if (breakWall2(matrix, wall, (Coordinate) {+1, 0})) {
                deckRemove(wallIndex, &deck);
                nbBreakWall++;
            }
        }
    }

    /* Matrix entrance */
    updateCase(matrix, 1, 0, VIDE, true);

    /* Matrix exit */
    updateCase(matrix, NB_LIG-2, NB_COL-1, VIDE, true);


    printf("Broken walls : %d\nTotal walls : %d\n", nbBreakWall, nbMaxWall);
    displayMatrix(matrix);
    deckDisplay(deck);
}

int breakWall2(int matrix[NB_LIG][NB_COL], Coordinate cWall, Coordinate shift) {
    /* Avoid breaking border walls */
    if (cWall.lig + shift.lig == 0 || cWall.lig + shift.lig == NB_LIG - 1 ||
        cWall.col + shift.col == 0 || cWall.col + shift.col == NB_COL - 1) {
        printf("Can't break border %d;%d\n", cWall.lig, cWall.col);
        return 0;
    }


    /* Avoid breaking a wall having the same case value on the other side */
    if (matrix[cWall.lig + shift.lig][cWall.col + shift.col] == matrix[cWall.lig - shift.lig][cWall.col - shift.col]) {
        return 0;
    }

    /* Break the wall */
    if (matrix[cWall.lig][cWall.col] == MUR) {
        matrix[cWall.lig][cWall.col] = matrix[cWall.lig + shift.lig][cWall.col + shift.col];
        updateCase(matrix, cWall.lig, cWall.col, matrix[cWall.lig][cWall.col], false);
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
void updateCase(int matrix[NB_LIG][NB_COL], int lig, int col, int value, int override) {
    if (matrix[lig][col] == MUR && !override)
        return;

    matrix[lig][col] = value;

    /* Update upper cases */
    if (lig - 1 > 0 && matrix[lig - 1][col] != matrix[lig][col])
        updateCase(matrix, lig - 1, col, value, false);

    /* Update lower cases */
    if (lig + 1 < NB_LIG - 1 && matrix[lig + 1][col] != matrix[lig][col])
        updateCase(matrix, lig + 1, col, value, false);

    /* Update left side cases */
    if (col - 1 > 0 && matrix[lig][col - 1] != matrix[lig][col])
        updateCase(matrix, lig, col - 1, value, false);

    /* Update right side cases */
    if (col + 1 < NB_COL - 1 && matrix[lig][col + 1] != matrix[lig][col])
        updateCase(matrix, lig, col + 1, value, false);
}

int getWalls(int matrix[NB_LIG][NB_COL], Coordinate **walls) {

    int nbWalls = 0;

    for (int i = 1; i < NB_LIG - 1; i++)
        for (int j = 1; j < NB_COL - 1; j++)
            if (matrix[i][j] == MUR)
                if (i % 2 != 0 || j % 2 != 0)
                    nbWalls++;


    (*walls) = malloc(nbWalls * sizeof(Coordinate));

    int indexWall = 0;
    for (int i = 1; i < NB_LIG - 1; i++)
        for (int j = 1; j < NB_COL - 1; j++)
            if (matrix[i][j] == MUR) {
                if (i % 2 != 0 || j % 2 != 0)
                    (*walls)[indexWall++] = (Coordinate) {i, j};
            }

    return nbWalls;
}
