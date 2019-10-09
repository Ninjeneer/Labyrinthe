#include <stdio.h>
#include "includes/labyrinthe.h"
#include "includes/display.h"

int main() {

    int **matrix;
    int playerChoice = displayMenu();
    int nbLig = 0, nbCol = 0;

    switch (playerChoice) {
        case CREATE:
            createMatrix(&nbLig, &nbCol, &matrix);
            break;

        case OPEN:
            break;

        case PLAY:
            break;

        case QUIT:
            return 0;

        default:
            printf("Unknown choice.");
            break;
    }

//int matrix[NB_LIG][NB_COL];
//
//generateStaticMatrix(matrix);
//generatePath2(matrix);
//displayMatrix(matrix);

    return 0;
}