/**
 * \file labyrinthe.c
 * \brief Contains all the function about the map structure.
 * \author Loan Alouache
 *
 * Contains all the function about the map structure.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "includes/game.h"
#include "includes/labyrinth.h"
#include "includes/display.h"
#include "includes/deck.h"


/**
 * Generate a static size matrix
 * @param matrix
 */
void generateStaticMatrix(Map *m) {
    /* Matrix memory allocation */
    m->matrix = (int **) malloc(m->nbRow * sizeof(int *));
    for (int i = 0; i < m->nbRow; i++)
        m->matrix[i] = (int *) malloc(m->nbCol * sizeof(int));

    /* Matrix initialization and border wall construction */
    for (int i = 0; i < m->nbRow; i++)
        for (int j = 0; j < m->nbCol; j++)
            if (i == 0 || i == m->nbRow - 1 || j == 0 || j == m->nbCol - 1)
                m->matrix[i][j] = WALL;
            else
                m->matrix[i][j] = i * m->nbRow + j;

    /* Inner horizontal wall construction */
    for (int i = 2; i < m->nbRow; i += 2)
        for (int j = 0; j < m->nbCol; j++)
            m->matrix[i][j] = WALL;

    /* Inner vertical wall construction */
    for (int i = 0; i < m->nbRow; i++)
        for (int j = 2; j < m->nbCol; j += 2)
            m->matrix[i][j] = WALL;


    generatePath(m);
}

/**
 * Generate the path through the matrix
 * @param m Map
 */
void generatePath(Map *m) {
    /* List of walls */
    Deck deck;
    deck.size = getWalls(m, &deck.walls);

    int nbBreakWall = 0;

    srand(time(NULL));
    while (nbBreakWall < (m->nbRow / 2) * (m->nbCol / 2) - 1) {
        /* Pick a random wall */
        int wallIndex = rand() % deck.size;
        Coordinate wall = deckRemove(wallIndex, &deck);

        /* Test if wall is breakable and break it */
        if (wall.row % 2 != 0 && wall.col % 2 == 0) {
            if (breakWall(m, wall, (Coordinate) {0, -1})) {
                //deckRemove(wallIndex, &deck);
                nbBreakWall++;
            }
            if (breakWall(m, wall, (Coordinate) {0, +1})) {
                //deckRemove(wallIndex, &deck);
                nbBreakWall++;
            }
        } else if (wall.row % 2 == 0 && wall.col % 2 != 0) {
            if (breakWall(m, wall, (Coordinate) {-1, 0})) {
                //deckRemove(wallIndex, &deck);
                nbBreakWall++;
            }
            if (breakWall(m, wall, (Coordinate) {+1, 0})) {
                //deckRemove(wallIndex, &deck);
                nbBreakWall++;
            }
        }
    }

    /* Matrix entrance */
    updateCase(m, MATRIX_START_LIG, MATRIX_START_COL, EMPTY, true);

    /* Matrix exit */
    updateCase(m, m->nbRow - 2, m->nbCol - 1, EMPTY, true);

    /* Generates treasures and traps */
    generateObjects(m);

    /* Breaks more walls if difficulty set to HARD */
    if (m->difficulty == HARD) {
        int nbBreakMax = (int) (deck.size * 0.2); /* Removes 20% of the remaining walls */
        nbBreakWall = 0;

        while (nbBreakWall < nbBreakMax) {
            /* Pick a random wall */
            int wallIndex = rand() % deck.size;
            Coordinate wall = deckRemove(wallIndex, &deck);
            updateCase(m, wall.row, wall.col, EMPTY, true);
            nbBreakWall++;
        }

        generateMonsters(m);
    }
}

/**
 * Break a given wall
 * @param m Map
 * @param cWall Wall coordinates
 * @param shift Case coordinates relative to the wall
 * @return 0 if fail, 1 if success
 */
int breakWall(Map *m, Coordinate cWall, Coordinate shift) {
    /* Avoid breaking border walls */
    if (cWall.row + shift.row == 0 || cWall.row + shift.row == m->nbRow - 1 ||
        cWall.col + shift.col == 0 || cWall.col + shift.col == m->nbCol - 1) {
        printf("Can't break border %d;%d\n", cWall.row, cWall.col);
        return 0;
    }

    /* Avoid breaking a wall having the same case value on the other side */
    if (m->matrix[cWall.row + shift.row][cWall.col + shift.col] ==
        m->matrix[cWall.row - shift.row][cWall.col - shift.col]) {
        return 0;
    }

    /* Break the wall */
    if (m->matrix[cWall.row][cWall.col] == WALL) {
        m->matrix[cWall.row][cWall.col] = m->matrix[cWall.row + shift.row][cWall.col + shift.col];
        updateCase(m, cWall.row, cWall.col, m->matrix[cWall.row][cWall.col], false);
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
    if (m->matrix[lig][col] == WALL && !override)
        return;

    m->matrix[lig][col] = value;

    /* Update upper cases */
    if (lig - 1 > 0 && m->matrix[lig - 1][col] != m->matrix[lig][col])
        updateCase(m, lig - 1, col, value, false);

    /* Update lower cases */
    if (lig + 1 < m->nbRow - 1 && m->matrix[lig + 1][col] != m->matrix[lig][col])
        updateCase(m, lig + 1, col, value, false);

    /* Update left side cases */
    if (col - 1 > 0 && m->matrix[lig][col - 1] != m->matrix[lig][col])
        updateCase(m, lig, col - 1, value, false);

    /* Update right side cases */
    if (col + 1 < m->nbCol - 1 && m->matrix[lig][col + 1] != m->matrix[lig][col])
        updateCase(m, lig, col + 1, value, false);
}

/**
 * Return a wall array and its size
 * @param m Map
 * @param walls Wall array
 * @return wall array size
 */
int getWalls(Map *m, Coordinate **walls) {

    int nbWalls = 0;

    for (int i = 1; i < m->nbRow - 1; i++)
        for (int j = 1; j < m->nbCol - 1; j++)
            if (m->matrix[i][j] == WALL)
                if (i % 2 != 0 || j % 2 != 0)
                    nbWalls++;


    (*walls) = malloc(nbWalls * sizeof(Coordinate));

    int indexWall = 0;
    for (int i = 1; i < m->nbRow - 1; i++)
        for (int j = 1; j < m->nbCol - 1; j++)
            if (m->matrix[i][j] == WALL) {
                if (i % 2 != 0 || j % 2 != 0)
                    (*walls)[indexWall++] = (Coordinate) {i, j};
            }

    return nbWalls;
}

/**
 * Generate objects on the map
 * @param m Map
 */
void generateObjects(Map *m) {
    int nbObjects = (int) (m->nbRow * m->nbCol * OBJECT_RATE);

    srand(time(NULL));
    while (nbObjects > 0) {
        Coordinate c;

        /* Random position */
        c.row = 1 + rand() % (m->nbRow - 2);
        c.col = 1 + rand() % (m->nbCol - 2);

        if (m->matrix[c.row][c.col] == EMPTY) {
            int objectType = TREASURE + rand() % 2; /* Random type */
            m->matrix[c.row][c.col] = objectType;

            nbObjects--;
        }
    }
}

/**
 * Generate the monsters
 * @param m Map
 */
void generateMonsters(Map *m) {
    int nbMonstersMax = 1;
//    int nbMonstersMax = (int)((m->nbRow * m->nbCol) * MONSTER_RATE);
    int nbMonsterCreated = 0;

    m->monsters = (Monster *) malloc(nbMonstersMax * sizeof(Monster));

    srand(time(NULL));
    while (nbMonsterCreated < nbMonstersMax) {

        Monster monster;

        /* Random position */
        monster.pos.row = 1 + rand() % (m->nbRow - 2);
        monster.pos.col = 1 + rand() % (m->nbCol - 2);

        monster.spawn = monster.pos;

        float radiusFactor = ((1 + rand() % 35) / 1000.0);
//        monster.radius = 2;
        monster.radius = (int) ((m->nbRow * m->nbCol) * radiusFactor);


        /* Random monster type */
//        monster.type = rand() % 2;
        monster.type = OGRE;

        if (m->matrix[monster.pos.row][monster.pos.col] == EMPTY) {
            printf("create with radius : %d", monster.radius);
            m->monsters[nbMonsterCreated] = monster;
            nbMonsterCreated++;
        }
    }

    m->nbMonsters = nbMonsterCreated;


}