//
// Created by lalouache on 02/10/19.
//

#include "labyrinthe.h"


void generateStaticMatrix(int matrix[NB_LIG][NB_COL]) {
     /* Matrix initialization and border wall construction */
     for (int i = 0; i < NB_LIG; i++)
         for (int j = 0; j < NB_COL; j++)
             if (i == 0 || i == NB_LIG-1 || j == 0 || j == NB_COL-1)
                 matrix[i][j] = MUR;
             else
                 matrix[i][j] = i * NB_LIG + j;

     /* Inner horizontal wall construction */
     for (int i = 2; i < NB_LIG; i += 2)
         for (int j = 0; j < NB_COL; j++)
             matrix[i][j] = MUR;

    /* Inner vertical wall construction */
    for (int i = 0; i < NB_LIG; i ++)
        for (int j = 2; j < NB_COL; j += 2)
            matrix[i][j] = MUR;

}
