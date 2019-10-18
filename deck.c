/**
 * \file deck.c
 * \brief Dynamic data structure.
 * \author Loan Alouache
 *
 * It makes easier the manipulation of arrays
 *
 */

#include <stddef.h>
#include <stdio.h>
#include "includes/deck.h"

void deckAdd(Deck *deck, Coordinate c) {
    deck->walls[deck->index] = c;
    deck->index++;
}

Coordinate deckPick(int index, Deck *deck) {
    return deck->walls[index];

}

Coordinate deckRemove(int index, Deck *deck) {
    Coordinate pickedWall = deck->walls[index];

    deck->walls[index] = deck->walls[deck->size-1];

    deck->size--;

    return pickedWall;
}

void deckDisplay(Deck d) {
    printf("(%d) => ", d.size);
    for (int i = 0; i < d.size; i++)
        printf("[%d;%d] ", d.walls[i].lig, d.walls[i].col);

    printf("\n");
}