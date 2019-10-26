/** ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students. No portion of this
 * document may be reproduced, copied or revised without written
 * permission of the authors.

 * \file deck.c
 * \brief Dynamic data structure.
 * \author Loan Alouache
 *
 * It makes easier the manipulation of arrays
 *
 */

#include <stdio.h>
#include "../includes/deck.h"

/**
 * Remove a wall from the deck
 * @param index index of the wall
 * @param deck the deck
 * @return Coordinates of the removed wall
 */
Coordinate deckRemove(int index, Deck *deck) {
    Coordinate pickedWall = deck->walls[index];

    deck->walls[index] = deck->walls[deck->size - 1];

    deck->size--;

    return pickedWall;
}

/**
 * Display the deck's content
 * @param d deck
 */
void deckDisplay(Deck d) {
    printf("(%d) => ", d.size);
    for (int i = 0; i < d.size; i++)
        printf("[%d;%d] ", d.walls[i].row, d.walls[i].col);

    printf("\n");
}