#include <stdio.h>
#include <stdlib.h>

typedef struct point_{
    double x, y;
} point;


typedef struct file_{
    point* points;
    int pointsAmount;
    int RminX;
    int RmaxX;
    int RminY;
    int RmaxY;
    FILE * dataFile;
    char name[50];
    int extrNum;
    int * JPoints;
    int flen;
} file;

file readPoints();
double psAngle(point* a, point* b, point* c);
double fastDist(point* a, point* b);
void extreme(file* data);
void Jarv(file* data);
int doIntersect(point* a0, point* a1, point* b0, point* b1);
int InPoly(file* data, point* p);

int main(int argc, char **argv) {
    int i;
    file points;
    point test;
    char deb = 'n';
    if(argc == 2){
        deb = argv[1][0];
    }

    points = readPoints();

    printf("Points amount is %d\n", points.pointsAmount);
    printf("Min and Max X range: %d %d\n", points.RminX, points.RmaxX);
    printf("Min and Max Y range: %d %d\n", points.RminY, points.RmaxY);

    extreme(&points);
    if(deb == 'd'){
        for(i = 0; i < points.pointsAmount; i++){
            printf("(%lf, %lf)\n", points.points[i].x, points.points[i].y);
        }
    }

    printf("\nextreme point: %lf %lf\n", points.points[points.extrNum].x, points.points[points.extrNum].y);

    Jarv(&points);
    printf("Number of vertexes: %d\n", points.flen-1);
    if(deb == 'd'){
        for(i = 0; i < points.flen; i++){
            printf("(%lf, %lf)\n", points.points[points.JPoints[i]].x, points.points[points.JPoints[i]].y);
        }
    }
    printf("\nEnter test point: ");
    scanf("%lf %lf", &test.x, &test.y);
    if(InPoly(&points, &test)){
        printf("This point lies in \'%s\' polygon\n\n", points.name);
    }else{
        printf("This point doesn't lie in \'%s\' polygon\n\n", points.name);
    }
    free(points.points);
    free(points.JPoints);
    return 0;
}

file readPoints(){
    file data;
    printf("\nEnter file name: ");
    scanf("%s", data.name);
    data.dataFile = fopen(data.name, "rb");
    data.JPoints = NULL;
    if(data.dataFile == NULL){
        printf("\nCan't find %s :(\n", data.name);
        exit(EXIT_FAILURE);
    }
    fread(&data.pointsAmount, sizeof(int), 1, data.dataFile);
    fread(&data.RminX, sizeof(int), 1, data.dataFile);
    fread(&data.RmaxX, sizeof(int), 1, data.dataFile);
    fread(&data.RminY, sizeof(int), 1, data.dataFile);
    fread(&data.RmaxY, sizeof(int), 1, data.dataFile);
    data.points = (point*)malloc(sizeof(point) * data.pointsAmount);
    fread(data.points, sizeof(point), data.pointsAmount, data.dataFile);
    fclose(data.dataFile);


    data.flen = 0;
    return data;
}

double psAngle(point* a, point* b, point* c){
    point vec0;
    point vec1;
    vec0.x = b->x-a->x;
    vec0.y = b->y-a->y;
    vec1.x = c->x-b->x;
    vec1.y = c->y-b->y;
    return ((vec0.x*vec1.y)-(vec1.x*vec0.y));
}

double fastDist(point* a, point* b){
    return ((b->x-a->x)*(b->x-a->x))+((b->y-a->y)*(b->y-a->y));
}

void extreme(file* data){
    int i;
    point axesP;
    double angle;
    double min;
    data->extrNum = 0;
    min = data->points[0].y;
    for(i = 1; i < data->pointsAmount; i++){
        if(data->points[i].y < min){
            min = data->points[i].y;
            data->extrNum = i;
        }
    }
    data->JPoints = malloc(sizeof(int)*data->pointsAmount);
    data->JPoints[0] = data->extrNum;
    data->flen = 1;

    axesP.x = data->points[data->extrNum].x - 1;
    axesP.y = data->points[data->extrNum].y;
    min = 3.15;
    for(i = 0; i < data->pointsAmount; i++){
        if(i == data->extrNum) continue;
        angle = psAngle(&axesP, &data->points[data->extrNum], &data->points[i]);
        if(angle < min && angle > 0){
            min = angle;
            data->JPoints[1] = i;
        }
    }
    data->flen++;
}

void Jarv(file* data){

double angle;

int index, i, n, l, q, j;

n = data->pointsAmount;
index = data->JPoints[0];
l = index;
j = 1;
while(1){
    q = (l + 1) % n;
    for(i = 0; i < n; i++){
        if(i == l) continue;
        angle = psAngle(&data->points[l], &data->points[i], &data->points[q]);
        if(angle > 0 ||
        (angle == 0 && (fastDist(&data->points[i], &data->points[l]) > fastDist(&data->points[q], &data->points[l]))))
        {
            q = i;
        }
    }
    l = q;
    if(l == index){
        break;
    }
    data->JPoints[j] = q;
    data->flen++;
    j++;
}

data->JPoints[data->flen-1] = data->JPoints[0];

data->JPoints = realloc(data->JPoints, data->flen);
}

int doIntersect(point* p00, point* p01, point* p10, point* p11){
    int p0 = (int)psAngle(p00, p01, p10);
    int p1 = (int)psAngle(p00, p01, p11);
    int p2 = (int)psAngle(p10, p11, p00);
    int p3 = (int)psAngle(p10, p11, p01);

    if((p0 ^ p1) < 0 && (p2 ^ p3) < 0 && p2 != p3 && p0 != p1){
        return 1;
    }
    return 0;
}

int InPoly(file* data, point* p){
    int i;
    point temp;
    int CountClock = 0;
    int Clock = 0;
    temp.y = p->y;
    temp.x = data->RmaxX;
    for(i = 1; i < data->flen; i++){
        if(doIntersect(p, &temp, &data->points[data->JPoints[i-1]], &data->points[data->JPoints[i]])){
            CountClock = 1;
            break;
        }
    }
    temp.x = data->RminX;
    for(i = 1; i < data->flen; i++){
        if(doIntersect(p, &temp, &data->points[data->JPoints[i-1]], &data->points[data->JPoints[i]])){
            Clock = 1;
            break;
        }
    }
    if(Clock == CountClock && Clock != 0){
        return 1;
    }else return 0;
}