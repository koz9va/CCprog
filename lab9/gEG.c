#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct point{
    double x, y;
};
int main() {
    struct point * points;
    int len;
    int i;
    int min[2];
    int max[2];
    FILE * file;
    srand(time(NULL));
    file = fopen("points", "wb");
    if(file == NULL){
        return 1;
    }
    printf("\nHow many?\n");
    scanf("%d", &len);
    fwrite(&len, sizeof(int), 1, file);
    printf("minimal x and y\n");
    scanf("%d %d", &min[0], &min[1]);
    fwrite(min, sizeof(int), 2, file);
    printf("maximums ");
    scanf("%d %d", &max[0], &max[1]);
    fwrite(max, sizeof(int), 2, file);
    points = (struct point*)malloc( len * sizeof(struct point));
    if(points == NULL)return 2;
    for(i = 0; i < len; i++){
        points[i].x = (((double) rand() / (double) RAND_MAX) * max[0] + min[0]);
        points[i].y = (((double) rand() / (double) RAND_MAX) * max[1] + min[1]);
    }
    fwrite(points, sizeof(struct point), len, file);
    free(points);
    return 0;
}