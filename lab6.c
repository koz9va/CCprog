
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorts.h"

FILE* dataFile;

int** allocMatrix(int COLLS, int ROWS){
    int** mat;
    int i;
    mat = (int**)calloc(ROWS, sizeof(int*));

    for(i = 0; i < ROWS; i++){
        mat[i] = (int*)calloc(COLLS, sizeof(int));
        memset(mat[i], 0, COLLS* sizeof(int));
        if(mat[i] == NULL)return 0;
    }
    if(mat == NULL || mat[0] == NULL){
        printf("There is an error in allocating memory for matrix");
        return NULL;
    }else{
        return mat;
    }
}

void reverse(int* input,int * out, int n){
    int temp, i;

    for(i = 0; i < n/2; i++){
        temp = input[n-i-1];
        out[n-i-1] = input[i];
        out[i] = temp;
    }
}

int main(){
    int temp, j;
    int i = 0;
    int ** table;
    int len = 0;
    int* array, *arrayCopy, *back, *bad, *backCopy, *badCopy, *nat;

    table = allocMatrix(5, 3);

    dataFile = fopen("l6v03.txt", "r");
    if(dataFile == NULL)return 21;

    while(fscanf(dataFile, "%d", &temp) != EOF){
        len++;
    }

    fseek(dataFile, 0l, SEEK_SET);

    array = calloc(len, sizeof(int));
    arrayCopy = calloc(len, sizeof(int));
    back = calloc(len, sizeof(int));
    backCopy = calloc(len, sizeof(int));
    bad = calloc(len, sizeof(int));
    badCopy = calloc(len, sizeof(int));
    nat = calloc(len, sizeof(int));


    while(fscanf(dataFile, "%d", &temp) != EOF){
        array[i] = temp;
        i++;
    }

    fclose(dataFile);

    memccpy(arrayCopy, array, len, len* sizeof(int));
    memccpy(backCopy, back, len, len* sizeof(int));
    memccpy(badCopy, bad, len, len* sizeof(int));

    for(i = 0; i < len; i++){
        nat[i] = i;
    }

    reverse(nat, back, len);
    memset(bad, 0, sizeof(int)*len);
    for(i = len; i > len/2; i--){
        bad[i] = 1;
    }

    //  for(i = 0; i < len; i++)printf("%d ", arrayCopy[i]);

    shaker(array, len, &table[0][0]);
    shaker(nat, len, &table[1][0]);
    shaker(back, len, &table[2][0]);

    memccpy(array, arrayCopy, len, len* sizeof(int));
    memccpy(back, backCopy, len, len* sizeof(int));

    insertionSort(array, len, &table[0][1]);
    insertionSort(nat, len, &table[1][1]);
    insertionSort(back, len, &table[2][1]);

    memccpy(array, arrayCopy, len, len* sizeof(int));
    memccpy(back, backCopy, len, len* sizeof(int));

    combSort(array, len, &table[0][2]);
    combSort(nat, len, &table[1][2]);
    combSort(back, len, &table[2][2]);

    memccpy(array, arrayCopy, len, len * sizeof(int));
    memccpy(back, backCopy, len, len * sizeof(int));

    QuickSort(array,0, len-1, &table[0][3]);
    QuickSort(nat,0, len-1, &table[1][3]);
    QuickSort(back,0, len-1, &table[2][3]);

    memccpy(array, arrayCopy, len, len * sizeof(int));
    memccpy(back, backCopy, len, len * sizeof(int));

    MergeSort(array, 0, len-1, &table[0][4]);
    MergeSort(nat,0,  len-1, &table[1][4]);
    MergeSort(back,0,  len-1, &table[2][4]);


    for(i = 0; i < 3; i++){
        for(j = 0; j < 5; j++){
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }

    return 0;
}