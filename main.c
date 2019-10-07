#include <stdio.h>
#include "includes/labyrinthe.h"
#include "includes/display.h"

int main() {

    int matrix[NB_LIG][NB_COL];

    //printf("%d %d ==> %d", 9/2, 23/2, (NB_LIG-2)*(NB_COL-2)-(44));



    generateStaticMatrix(matrix);
    generatePath2(matrix);
//    displayMatrix(matrix);

    return 0;
}