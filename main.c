#include <stdio.h>
#include "labyrinthe.h"
#include "display.h"

int main() {

    int matrix[NB_LIG][NB_COL];

    generateStaticMatrix(matrix);
    generatePath(matrix);
    displayMatrix(matrix);




    return 0;
}