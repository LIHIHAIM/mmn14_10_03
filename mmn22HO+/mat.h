
/* [mmn 22 - header file]
In this file there are the prototypes of functions from mat.c, and the common includes 
and defenitions requaiered in the mat.c and mymat.c files.

Author: Uri K.H.    ID: 215105321    
Tutor: Danny        Date: 31.12.2020 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 4 /* The size of the matrix */

typedef double mat[SIZE][SIZE]; /* Defenition of a matrix: size 4x4 and includes decimal numbers only */

/* Prototypes of functions from mat.c */
void print_mat(mat *);
void read_mat(mat*,double*);
void add_mat(mat*,mat*,mat*);
void sub_mat(mat*,mat*,mat*);
void mul_mat(mat*,mat*,mat*);
void mul_scalar(mat*,double,mat*);
void trans_mat(mat*,mat*);
void stop(void);
