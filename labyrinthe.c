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
void generateStaticMatrix(Map *m) {
    /* Matrix memory allocation */
    m->matrix = malloc(m->nbLig * sizeof(int*));
    for (int i = 0; i < m->nbLig; i++)
        m->matrix[i] = malloc(m->nbCol * sizeof(int));

    /* Matrix initialization and border wall construction */
    for (int i = 0; i < m->nbLig; i++)
        for (int j = 0; j < m->nbCol; j++)
            if (i == 0 || i == m->nbLig - 1 || j == 0 || j == m->nbCol - 1)
                m->matrix[i][j] = MUR;
            else
                m->matrix[i][j] = i * m->nbLig + j;

    /* Inner horizontal wall construction */
    for (int i = 2; i < m->nbLig; i += 2)
        for (int j = 0; j < m->nbCol; j++)
            m->matrix[i][j] = MUR;

    /* Inner vertical wall construction */
    for (int i = 0; i < m->nbLig; i++)
        for (int j = 2; j < m->nbCol; j += 2)
            m->matrix[i][j] = MUR;


    //generatePath(m);
}

void generatePath(Map *m) {
    Deck deck;
    deck.size = getWalls(m, &deck.walls);

    int nbBreakWall = 0;
    int nbMaxWall = deck.size;

    srand(time(NULL));
    while (nbBreakWall < (m->nbLig / 2) * (m->nbCol / 2) - 1) {
        int wallIndex = rand() % deck.size;
        Coordinate wall = deckPick(wallIndex, &deck);

        if (wall.lig % 2 != 0 && wall.col % 2 == 0) {
            if (breakWall(m, wall, (Coordinate) {0, -1})) {
                deckRemove(wallIndex, &deck);
                nbBreakWall++;
            }
            if (breakWall(m, wall, (Coordinate) {0, +1})) {
                deckRemove(wallIndex, &deck);
                nbBreakWall++;
            }
        } else if (wall.lig % 2 == 0 && wall.col % 2 != 0) {
            if (breakWall(m, wall, (Coordinate) {-1, 0})) {
                deckRemove(wallIndex, &deck);
                nbBreakWall++;
            }
            if (breakWall(m, wall, (Coordinate) {+1, 0})) {
                deckRemove(wallIndex, &deck);
                nbBreakWall++;
            }
        }
    }

    /* Matrix entrance */
    updateCase(m, 1, 0, VIDE, true);

    /* Matrix exit */
    updateCase(m, m->nbLig - 2, m->nbCol - 1, VIDE, true);
}

int breakWall(Map *m, Coordinate cWall, Coordinate shift) {
    /* Avoid breaking border walls */
    if (cWall.lig + shift.lig == 0 || cWall.lig + shift.lig == m->nbLig - 1 ||
        cWall.col + shift.col == 0 || cWall.col + shift.col == m->nbCol - 1) {
        printf("Can't break border %d;%d\n", cWall.lig, cWall.col);
        return 0;
    }


    /* Avoid breaking a wall having the same case value on the other side */
    if (m->matrix[cWall.lig + shift.lig][cWall.col + shift.col] ==
        m->matrix[cWall.lig - shift.lig][cWall.col - shift.col]) {
        return 0;
    }

    /* Break the wall */
    if (m->matrix[cWall.lig][cWall.col] == MUR) {
        m->matrix[cWall.lig][cWall.col] = m->matrix[cWall.lig + shift.lig][cWall.col + shift.col];
        updateCase(m, cWall.lig, cWall.col, m->matrix[cWall.lig][cWall.col], false);
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
void updateCase(Map *m, int lig, int col, int value, int override) {
    if (m->matrix[lig][col] == MUR && !override)
        return;

    m->matrix[lig][col] = value;

    /* Update upper cases */
    if (lig - 1 > 0 && m->matrix[lig - 1][col] != m->matrix[lig][col])
        updateCase(m, lig - 1, col, value, false);

    /* Update lower cases */
    if (lig + 1 < m->nbLig - 1 && m->matrix[lig + 1][col] != m->matrix[lig][col])
        updateCase(m, lig + 1, col, value, false);

    /* Update left side cases */
    if (col - 1 > 0 && m->matrix[lig][col - 1] != m->matrix[lig][col])
        updateCase(m, lig, col - 1, value, false);

    /* Update right side cases */
    if (col + 1 < m->nbCol - 1 && m->matrix[lig][col + 1] != m->matrix[lig][col])
        updateCase(m, lig, col + 1, value, false);
}

int getWalls(Map *m, Coordinate **walls) {

    int nbWalls = 0;

    for (int i = 1; i < m->nbLig - 1; i++)
        for (int j = 1; j < m->nbCol - 1; j++)
            if (m->matrix[i][j] == MUR)
                if (i % 2 != 0 || j % 2 != 0)
                    nbWalls++;


    (*walls) = malloc(nbWalls * sizeof(Coordinate));

    int indexWall = 0;
    for (int i = 1; i < m->nbLig - 1; i++)
        for (int j = 1; j < m->nbCol - 1; j++)
            if (m->matrix[i][j] == MUR) {
                if (i % 2 != 0 || j % 2 != 0)
                    (*walls)[indexWall++] = (Coordinate) {i, j};
            }

    return nbWalls;
}
