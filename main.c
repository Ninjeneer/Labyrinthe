#include <stdio.h>
#include "includes/labyrinthe.h"
#include "includes/display.h"

int main() {

    int matrix[NB_LIG][NB_COL];

    generateStaticMatrix(matrix);
    generatePath(matrix);
    displayMatrix(matrix);

    return 0;
}