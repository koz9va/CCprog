//
// Created by Серафим Гончаров on 4/6/20.
//
#include "sorts.h"
void bubble(int* arr,int n, int* count) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        int sorting = 0;

        for (j = 0; j < n - i - 1; j++) {
            (*count)++;
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j + 1] = temp;
                sorting++;
            }
        }
        if (sorting == 0) {
            break;
        }
    }

}

void shaker(int* arr, int n, int* count){
    int i, temp;
    int swapped = true;
    int start = 0;
    int end = n-1;

    while(swapped){
        swapped = false;

        for(i = start; i < n; ++i){
            ++(*count);
            if(arr[i] > arr[i+1]){
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;

                swapped = true;

            }
        }

        if(!swapped)
            break;

        swapped = false;

        --end;

        for(i = end - 1; i >= start; --i){
            ++(*count);
            if(arr[i] > arr[i + 1]){
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
        }

        ++start;


    }


}

void combSort(int* arr, int n, int* count){

    int gap = n;
    int temp;


    int swapped = true;

    while (gap != 1 || swapped == true)
    {

        gap = (gap*10)/13;

        if (gap < 1)
            gap = 1;


        swapped = false;


        for (int i=0; i<n-gap; i++)
        {
            (*count)++;
            if (arr[i] > arr[i+gap])
            {
                temp = arr[i];
                arr[i] = arr[i+gap];
                arr[i+gap] = temp;
                swapped = true;
            }
        }
    }

}

void insertionSort(int* arr, int n, int* count){
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        (*count)++;

        while (j >= 0 && arr[j] > key) {
            (*count)++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void shellSort(int* arr, int n, int* count){
    int i, gap, temp, j;

    for(gap = n/2; gap > 0; gap /= 2){

        for (i = gap; i < n; i += 1)
        {
            temp = arr[i];

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                (*count)++;
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }

}


void GnomeSort(int* arr, int n, int* count){

    int index = 0;
    int temp;

    while (index < n) {
        (*count)++;
        if (index == 0)
            index++;
        if (arr[index] >= arr[index - 1])
            index++;
        else {
            temp = arr[index];
            arr[index] = arr[index - 1];
            arr[index-1] = temp;
            index--;
        }
    }

}

void SelectionSort(int* arr, int n, int* count){
    int i, j, min_idx, temp;

    for (i = 0; i < n-1; i++)
    {

        min_idx = i;
        for (j = i+1; j < n; j++){
            (*count)++;
            if (arr[j] < arr[min_idx]){
                min_idx = j;

            }

        }


        temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}
int partition(int* arr, int low, int high, int* count){
    int temp;
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        (*count)++;
    }
    temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}
void QuickSort(int* arr, int low, int high, int* count){

    int pi = partition(arr, low, high, count);
    (*count)++;
    if(low < high){
        QuickSort(arr, low, pi - 1, count);
        QuickSort(arr, pi + 1, high, count);
    }


}

void merge(int* arr, int l, int m, int r, int* count){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2];


    for (i = 0; i < n1; i++){
        (*count)++;
        L[i] = arr[l + i];
    }

    for (j = 0; j < n2; j++){
        (*count)++;

        R[j] = arr[m + 1+ j];
    }


    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        (*count)++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }


    while (i < n1)
    {
        (*count)++;
        arr[k] = L[i];
        i++;
        k++;
    }


    while (j < n2)
    {
        (*count)++;
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(int* arr, int l, int r, int* count){
    (*count)++;
    if (l < r)
    {
        int m = l+(r-l)/2;

        MergeSort(arr, l, m, count);
        MergeSort(arr, m+1, r, count);

        merge(arr, l, m, r, count);
    }
}

void CountSort(int* arr, int n, int* count){
    int* output = calloc(n, sizeof(int));

    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        (*count)++;
        if (arr[i] > max)
            max = arr[i];
    }

    int* countArr = calloc(max+1, sizeof(int));
    for (int i = 0; i <= max; ++i)
    {
        (*count)++;
        countArr[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        (*count)++;
        countArr[arr[i]]++;
    }
    for (int i = 1; i <= max; i++)
    {
        (*count)++;
        countArr[i] += countArr[i - 1];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        (*count)++;
        output[countArr[arr[i]] - 1] = arr[i];
        countArr[arr[i]]--;
    }
    for (int i = 0; i < n; i++)
    {
        (*count)++;
        arr[i] = output[i];
    }
}