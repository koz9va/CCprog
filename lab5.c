//
// Created by Серафим Гончаров on 3/27/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vector {

    double x, y, z;
    struct vector *next;

} vec;

vec *pushToList(vec *_elem) {
    if (_elem->next != NULL) return NULL;
    vec *res = malloc(sizeof(vec));
    if (res == NULL)printf("Error in allocating new vec\n");
    _elem->next = res;
    res->next = NULL;
    return res;
}

void freeList(vec *first) {
    vec *itter = first;
    while (itter->next != NULL) {
        next = itter->next;
        free(itter);
        itter = next;
    }

}

double dotProduct(vec *a, vec *b) {
    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

double module(vec *a) {
    return sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}

double angle(vec *a, vec *b) {
    return acos(dotProduct(a, b)) / (module(a) * module(b));
}

vec *vectorProduct(vec *a, vec *b, vec *sum) {
    if (a == NULL || b == NULL || sum == NULL) return NULL;
    sum->x = a->x + b->x;
    sum->y = a->y + b->y;
    sum->z = a->z + b->z;
    return sum;
}

vec *CrossProduct(vec *a, vec *b, vec *prod) {
    if (a == NULL || b == NULL || prod == NULL) return NULL;
    prod->x = a->y * b->z - a->z * b->y;
    prod->y = a->z * b->x - a->x * b->z;
    prod->z = a->x * b->y - a->y * b->x;
    return prod;
}

vec *vectorByNum(vec *a, double num, vec *res) {
    if (a == NULL) return NULL;
    if (res == NULL) {
        a->x *= num;
        a->y *= num;
        a->z *= num;
    } else {
        res->x = a->x * num;
        res->y = a->y * num;
        res->z = a->z * num;
    }
    return res;
}

FILE *dataFile;


int main() {

    int vecLen = 0;

    vec result;
    result.next = NULL;

    vec *start = malloc(sizeof(vec));
    vec *itter;
    itter = start;

    start->next = NULL;

    dataFile = fopen("l05v03.txt", "r");

    if(dataFile == NULL){
        printf("There is an error in the opening file\n");
        return 13;
    }

    while (EOF != fscanf(dataFile, "%lf %lf %lf", &itter->x, &itter->y, &itter->z)) {
        itter = pushToList(itter);
        vecLen++;
    }

    fclose(dataFile);
    itter = start;


    while (itter) {
        printf("%lf\t%lf\t%lf\n", itter->x, itter->y, itter->z);
        itter = itter->next;
    }
    printf("There are %d elements in the list\n", vecLen);

    vectorProduct(start, itter, &result);

    printf("\n\n%lf\t%lf\t%lf\n", result.x, result.y, result.z);

    freeList(start);

    return 0;
}
