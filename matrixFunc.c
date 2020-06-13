//
// Created by Серафим Гончаров on 07.03.2020.
//
#include "matrixFunc.h"
int** allocMatrix(int COLLS, int ROWS){
    int** mat;
    int i;
    mat = (int**)calloc(ROWS, sizeof(int*));

    for(i = 0; i < ROWS; i++){
        mat[i] = (int*)calloc(COLLS, sizeof(int));
        memset(mat[i], 0, COLLS);
        if(mat[i] == NULL)return 0;
    }
    if(mat == NULL || mat[0] == NULL){
        printf("There is an error in allocating memory for matrix");
        return NULL;
    }else{
        return mat;
    }
}


void swap(int* a, int* b, int len){
    int temp;
    int i;
    for(i = 0; i < len; i++){
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}
// extswap – "extended swap" replaces one column with another over the arrays in matrix. For user
// it looks like an usual swap of two arrays
void extswap(int** mat, int ROWS, int a, int b){
    int i, temp;

    for(i = 0; i < ROWS; i++){
        temp = mat[i][a];
        mat[i][a] = mat[i][b];
        mat[i][b] = temp;
    }

}

int** transposeMatrix(int** input,  int ROWS, int COLLS){
    int i, j;
    int** out = allocMatrix(COLLS, ROWS);

    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLLS; j++){
            out[i][j] = input[j][i];
        }
    }


    return out;
}

void bubble(int* arr,int* nums , int n) {
    int i, j, temp, tempn;
    for (i = 0; i < n - 1; i++) {
        int sorting = 0;

        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                tempn = nums[j];
                arr[j] = arr[j+1];
                nums[j] = nums[j+1];
                arr[j + 1] = temp;
                nums[j+1] = tempn;
                sorting++;
            }
        }
        if (sorting == 0) {
            break;
        }
    }

}

void printMatrix(struct matrix_* a){
    int i, j;
    for(i = 0; i < a->rows; i++){
        for(j = 0; j < a->colls; j++){
            printf("%d ", a->mat[i][j]);
        }
        printf("\n");
    }
}

void cutByRows(struct matrix_* a){
    int i, j;
    int** del = a->mat;
    a->mat = allocMatrix(a->colls, a->colls);
    for(i = 0; i < a->colls; i++){
        for(j = 0; j < a->colls; j++){
            a->mat[i][j] = del[i][j];
        }
    }
    for(i = 0; i < a->rows; i++){
        free(del[i]);
    }
    free(del);

    a->rows = a->colls;

}
void calcQuad(struct quadrant* q){
    if(q->num == 1){
        q->i0 = 0;
        q->is = 1;
        q->il = q->RowMid+1;
        q->j0 = q->CollsMid+1;
        q->js = 1;
        q->jl  = q->CollsMid+1;
    }
    if(q->num == 2){
        q->i0 = 0;
        q->is = 1;
        q->il = q->RowMid;
        q->j0 = 0;
        q->js = 1;
        q->jl = q->CollsMid;
    }
    if(q->num == 3){
        q->i0 = q->RowMid+1;
        q->is = 1;
        q->il = q->RowMid*2;
        q->j0 = 0;
        q->js = 1;
        q->jl = q->CollsMid+1;
    }

    if(q->num == 4){
        q->i0 = q->RowMid+1;
        q->is = 1;
        q->il = q->RowMid*2;
        q->j0 = q->CollsMid+1;
        q->js = 1;
        q->jl = q->CollsMid*2;
    }

}
void swapQuadrants(int quad0, int quad1, struct matrix_* a){
    if(quad0 == quad1)printf("Warning: quadrants are the same\n");

    if(quad0 < 1 || quad0 > 4 || quad1 < 1 || quad1 > 4){
        printf("quadrants are out of possible range\n");
        return;
    }



    int i, j, temp;
    short qRowMid = 0;
    short qCollMid = 0;
    struct matrix_ qMat0;
    struct matrix_ qMat1;
    struct quadrant q0, q1;

    q0.num = quad0;
    q1.num  = quad1;



        qRowMid = a->rows/2;

        qCollMid = a->colls/2;



    qMat0.mat = allocMatrix(qCollMid, qRowMid);
    qMat1.mat = allocMatrix(qCollMid, qRowMid);
    qMat0.rows = qRowMid;
    qMat1.rows = qRowMid;
    qMat0.colls = qCollMid;
    qMat1.colls = qCollMid;


    q0.RowMid = qRowMid;
    q1.RowMid = qRowMid;
    q0.CollsMid = qCollMid;
    q1.CollsMid = qCollMid;

    calcQuad(&q0);
    calcQuad(&q1);

   for(i = 0; i < q0.RowMid; i++){
       for(j = 0; j < q0.CollsMid; j++){
           qMat0.mat[i][j] = a->mat[q0.i0+(i*q0.is)][q0.j0+(j*q0.js)];
           qMat1.mat[i][j] = a->mat[q1.i0+(i*q1.is)][q1.j0+(j*q1.js)];
       }
   }

    for(i = 0; i < q0.RowMid; i++){
        for(j = 0; j < q0.CollsMid; j++){
            a->mat[q0.i0+(i*q0.is)][q0.j0+(j*q0.js)] = qMat1.mat[i][j];
            a->mat[q1.i0+(i*q1.is)][q1.j0+(j*q1.js)] = qMat0.mat[i][j];
        }
    }


}