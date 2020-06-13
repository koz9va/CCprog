//
// Created by Серафим Гончаров on 4/6/20.
//

#ifndef INF1_2_SORTS_H
#define INF1_2_SORTS_H
#define true 1
#define false 0
#include <stdlib.h>


void bubble(int* arr,int n, int* count);
void shaker(int* arr, int n, int* count);
void combSort(int* arr, int n, int* count);
void insertionSort(int* arr, int n, int* count);
void shellSort(int* arr, int n, int* count);
void GnomeSort(int* arr, int n, int* count);
void SelectionSort(int* arr, int n, int* count);
int partition(int* arr, int low, int high, int* count);
void QuickSort(int* arr, int low, int high, int* count);
void merge(int* arr, int l, int m, int r, int* count);
void MergeSort(int* arr, int l, int r, int* count);
void CountSort(int* arr, int n, int* count);


#endif //INF1_2_SORTS_H
