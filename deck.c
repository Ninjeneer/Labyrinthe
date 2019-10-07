//
// Created by loan on 07/10/19.
//

#include <stddef.h>
#include <stdio.h>
#include "includes/deck.h"

void deckAdd(Deck *deck, Coordinate c) {
    deck->walls[deck->index] = c;
    deck->index++;
}

Coordinate deckPick(int index, Deck *deck) {
    Coordinate pickedWall = deck->walls[index];

    for (int i = index; i < deck->size; i++)
        deck->walls[i] = deck->walls[i + 1];

    deck->size--;

    return pickedWall;
}

void deckDisplay(Deck d) {
    for (int i = 0; i < d.size; i++)
        printf("[%d;%d] ", d.walls[i].lig, d.walls[i].col);

    printf("\n");
}