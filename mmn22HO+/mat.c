
/* [mmn 22: mat.c]
This file contains the possible functions the user of the calculator can 
oprate on matrices.
The functions in this file are not returning any values.

Author: Uri K.H.    ID: 215105321    
Tutor: Danny        Date: 31.12.2020 */

#include "mat.h"

/* read_mat: Inserts decimal values from an decimal numbers array into the matrix
which the pointer to it was given as a parameter. */
void read_mat(mat *matrix, double *params){
     int i, j, paramsInd = 0;
     for(i = 0; i < SIZE && paramsInd < SIZE*SIZE; i++)
          for(j = 0; j < SIZE && paramsInd < SIZE*SIZE; j++, paramsInd++)
               (*matrix)[i][j] = params[paramsInd];              
     return;
}

/* print_mat: Printing a visual representation of the matrix which a pointer to it
 was given as a parameter. */
void print_mat(mat *matrix){
     int i, j;
     printf("your mat:\n");
     for(i = 0; i < SIZE; i++){
          for(j = 0; j < SIZE; j++)
               printf("%-.2f\t", (*matrix)[i][j]);
          printf("\n");
     }
     return;
}

/* add_mat: Adds the values from the first matrix and the values from the second matrix 
 and saves the result in the thisd matrix. Every parameter is a pointer to a matrix. */
void add_mat(mat *mtrx1, mat *mtrx2, mat *result){
     int i, j;
     for(i = 0; i < SIZE; i++)
          for(j = 0; j < SIZE; j++)
               (*result)[i][j] = (*mtrx1)[i][j] + (*mtrx2)[i][j];
     return;
}

/* sub_mat: Substructs the values from the second matrix from the values of the first matrix 
 and saves the result in the thisd matrix. Every parameter is a pointer to a matrix. */
void sub_mat(mat *mtrx1, mat *mtrx2, mat *result){
     int i, j;
     for(i = 0; i < SIZE; i++)
          for(j = 0; j < SIZE; j++)
               (*result)[i][j] = (*mtrx1)[i][j] - (*mtrx2)[i][j];
     return;
}

/* mul_mat: Multiplies the first matrix and the second matrix and and saves the result in 
the thisrd matrix. Every parameter is a pointer to a matrix. */
void mul_mat(mat *mtrx1, mat *mtrx2, mat *result){
     int row1, col1, row2, col2, i, j;
     mat temp = {0};
     /* Inserting the values of the operation into the temporary matrix */
     for(col1 = 0; col1 < SIZE; col1++)
          for(row2 = 0; row2 < SIZE; row2++)
               for(row1 = 0, col2 = 0; row1 < SIZE && col2 < SIZE; row1++, col2++)
                    (temp)[row2][col1] += (*mtrx1)[row1][col1] * (*mtrx2)[row2][col2];

     /* Inserting the values form the temporary matrix into the result matrix */
     for(i = 0; i < SIZE; i++)
          for(j = 0; j < SIZE; j++)
               (*result)[i][j] = temp[i][j];
     return;
}

/* mul_scalar: Multiplies every value of the first matrix with the given scalar and 
 saves the result of the operation in the second matrix. Every matrix is given as a
 pointer to it. */
void mul_scalar(mat *matrix, double scalar, mat *result){
     int i, j;
     for(i = 0; i < SIZE; i++)
          for(j = 0; j < SIZE; j++)
               (*result)[i][j] = ((*matrix)[i][j]) * scalar;
     return;
}

/* trans_mat: Transpose the first matrix and saves the result of the operation in the second matrix.
 Every matrix is given as a pointer to it.*/
void trans_mat(mat *matrix, mat *result){
     int i, j;
     mat temp = {0};
     /* Inserting the values into the temporary matrix */
     for(i = 0; i < SIZE; i++)
          for(j = 0; j < SIZE; j++)
               temp[j][i] = (*matrix)[i][j];

     /* Inserting the values form the temporary matrix into the result matrix */
     for(i = 0; i < SIZE; i++)
          for(j = 0; j < SIZE; j++)
               (*result)[i][j] = temp[i][j];
     return;
}

/* stop: Terminates the program naturaly and prints to the user that the program was terminated. 
 (stop() does not have any parameters). */
void stop(void){
     printf("\n\t--program has been terminated--\n");
     exit(0);
}
