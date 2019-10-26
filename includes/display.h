#ifndef PROJET1_DISPLAY_H
#define PROJET1_DISPLAY_H

#include "labyrinth.h"
#include "game.h"

#define MESSAGE_BUFFER_SIZE 255

/* Ansi colors */
#define RESET "\033[0m"
#define YELLOW "\033[0;33m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define MAGENTA "\033[0;35m"
#define BLUE "\033[1;34m"

enum { CREATE, OPEN, PLAY, LEADERBOARD, QUIT};

void displayGame(Map *m, Player p, const char message[MESSAGE_BUFFER_SIZE]);
void displayTitle();
int displayMenu();
void createMap(Map *m);
void openMap(Map *m);
void clearBuffer();
int showFileList();
void askScore(Map *m, Player *p, Leaderboard *l, int add);
void showLeaderboard(Map m);
int displayMonsters(Map *m, int lig, int col);
void pressAnyKey();


#endif /* PROJET1_DISPLAY_H */
