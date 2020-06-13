//
// Created by Серафим Гончаров on 3/2/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input;

int** allocMatrix(int COLLS, int ROWS){
    int** mat;
    int i;
    mat = (int**)malloc(ROWS*sizeof(int*));

    for(i = 0; i < ROWS; i++){
        mat[i] = (int*)malloc(COLLS*sizeof(int));
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
void extswap(int** mat, const int ROWS, const int a, const int b){
    int i, temp;

    for(i = 0; i < ROWS; i++){
        temp = mat[i][a];
        mat[i][a] = mat[i][b];
        mat[i][b] = temp;
    }

}

int** transposeMatrix(const int** input, const int COLLS, const int ROWS){
    int** out = allocMatrix(ROWS, COLLS);



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
void printMartix(int** a, int Rows, int Colls){
    int i, j;
    for(i = 0; i < Rows; i++){
        for(j = 0; j < Colls; j++){
            printf("%d ", *(*(a+i)+j));
        }
        printf("\n");
    }
}

int main(){
    int colls = 0, rows = 0;
    int** matrix;
    int** matrixT;
    int* addRow, addColl;
    int i, j;
    char c;
    int* quadRow;
    int* quadColl;
    int* quadRowPos;
    int* quadCollPos;
    int deb = 0;
    input = fopen("l4v03.txt", "r");
    if(input == NULL){
        printf("There is an error in opening the file");
        return 1;
    }
    i = 0;
    while(i < 1e5){
        i++;
        c = getc(input);
        if(c == 32 && rows == 0){
            colls++;
            continue;
        }
        if(c == 10){
            rows++;
            continue;
        }
        if(c == EOF)break;
    }
    if(i == 1e5){
        printf("It seems like a strange activity");
        return 1;
    }
    fseek(input, 0L, SEEK_SET);

    matrix = allocMatrix(colls, rows);

    quadRow = malloc(sizeof(int)*rows);
    quadRowPos = malloc(sizeof(int)*rows);
    if(quadRow == NULL) return 2;
    memset(quadRow, 0, rows);

    quadColl = malloc(sizeof(int)*colls);
    quadCollPos = malloc(sizeof(int)*colls);
    if(quadColl == NULL) return 2;
    memset(quadColl, 0, colls);

    for(i = 0; i < rows; i++){
        quadRowPos[i] = i;
        for(j = 0; j < colls; j++){
            quadCollPos[j] = j;
            fscanf(input, "%d", (*(matrix+i)+j));
        }
    }

    for(i = 0; i < rows; i++){
        for(j = 0; j < colls; j++){
            quadRow[i] += (*(*(matrix+i)+j))*(*(*(matrix+i)+j));

            quadColl[j] += matrix[i][j]*matrix[i][j];

        }

    }
//printf("%d",*(*(matrix+1)+2));
    printf("source matrix:\n");
    printMartix(matrix, rows, colls);
    printf("\n");
    bubble(quadRow, quadRowPos, rows);
    bubble(quadColl, quadCollPos, colls);
    for(i = 0; i < rows; i++){
        printf("%d  %d\n", quadRowPos[i], quadRow[i]);

    }
    printf("\n");
    for(i = 0; i < colls; i++){
        printf("%d ", quadColl[i]);
    }

    swap(matrix[1], matrix[0], rows);

   for(i = 0; i < rows; i++){
        swap(matrix[quadRowPos[i]], matrix[i], rows);
    }
printf("\n\n");
//    for(i = 0; i < rows; i++){
//        printf("%d\n", matrix[quadRowPos[i]][0]);
//    }


printf("----------------\n");

//    for(i = 0; i < colls; i++){
//        printf("%d ", matrix[0][quadCollPos[i]]);
//    }

    printMartix(matrix, rows, colls);
    printf("\n----------\n");
    extswap(matrix, rows, 0, 1);
    printMartix(matrix, rows, colls);


    for(i = 0; i < rows; i++){
        free(matrix[i]);
    }
    for(i = 0; i < colls; i++){
        free(matrixT[i]);
    }
    free(matrix);
    free(matrixT);
    free(quadColl);
    free(quadCollPos);
    free(quadRow);
    free(quadRowPos);
    return 0;
}
