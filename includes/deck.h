/** ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students. No portion of this
 * document may be reproduced, copied or revised without written
 * permission of the authors.
 */

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

#endif /* PROJET1_DECK_H */
