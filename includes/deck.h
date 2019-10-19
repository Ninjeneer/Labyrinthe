//
// Created by loan on 07/10/19.
//

#ifndef PROJET1_DECK_H
#define PROJET1_DECK_H

#include "labyrinth.h"

typedef struct {
    Coordinate *walls;
    int size;
    int index;
} Deck;

void deckAdd(Deck *deck, Coordinate c);
Coordinate deckPick(int index, Deck *deck);
Coordinate deckRemove(int index, Deck *deck);
void deckDisplay(Deck d);

#endif //PROJET1_DECK_H
