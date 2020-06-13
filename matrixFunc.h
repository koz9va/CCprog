//
// Created by Серафим Гончаров on 07.03.2020.
//

#ifndef INF1_2_MATRIXFUNC_H
#define INF1_2_MATRIXFUNC_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

struct matrix_{
    int** mat;
    int colls;
    int rows;
};
struct quadrant{
    int  is, js, il, jl, i0, j0,RowMid, CollsMid;
    int num;
};

int** allocMatrix(int COLLS, int ROWS);

void swap(int* a, int* b, int len);
// extswap – "extended swap" replaces one column with another over the arrays in matrix. For user
// it looks like an usual swap of two arrays
void extswap(int** mat, int ROWS, int a, int b);

int** transposeMatrix(int** input,  int ROWS, int COLLS);

void bubble(int* arr,int* nums , int n);
void printMatrix(struct matrix_* a);
void cutByRows(struct matrix_* a);
void calcQuad(struct quadrant* q);
void swapQuadrants(int quad0, int quad1, struct matrix_* a);


#endif //INF1_2_MATRIXFUNC_H
