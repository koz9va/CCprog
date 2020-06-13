#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct point_{
    double x, y;
} point;


int main() {
    point * points;
    int pointsAmount;
    char fileName[50];
    int RminX;
    int RmaxX;
    int RminY;
    int RmaxY;
    int i;
    FILE * dataFile;
    srand(time(NULL));
    printf("\nEnter file name: ");
    scanf("%s", fileName);
    dataFile = fopen(fileName, "wb");
    if(dataFile == NULL){
        printf("Can't create a file with this name :(");
        return 21;
    }
    printf("\nEnter amount of points: ");
    scanf("%d", &pointsAmount);
    printf("\nEnter minimum value of x after that of y: ");
    scanf("%d %d", &RminX, &RminY);
    printf("\nEnter maximum value of x and y: ");
    scanf("%d %d", &RmaxX, &RmaxY);

    points = (point*)malloc(sizeof(point)*pointsAmount);

    for(i = 0; i < pointsAmount; i++){
        points[i].x = (((double) rand() / (double) RAND_MAX) * RmaxX + RminX);
        points[i].y = (((double) rand() / (double) RAND_MAX) * RmaxY + RminY);
    }
    fwrite(&pointsAmount, sizeof(int), 1, dataFile);
    fwrite(&RminX, sizeof(int), 1, dataFile);
    fwrite(&RmaxX, sizeof(int), 1, dataFile);
    fwrite(&RminY, sizeof(int), 1, dataFile);
    fwrite(&RmaxY, sizeof(int), 1, dataFile);
    fwrite(points, sizeof(point), pointsAmount, dataFile);
    printf("\nPoints are generated and written to %s\n\n", fileName);
    free(points);
    return 0;
}