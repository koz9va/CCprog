#include <stdio.h>
#include <stdlib.h>
struct point{
    double x, y;
};

struct pointsArr{
    struct point * ptr;
    int len;
    int min[2];
    int max[2];
};

struct list{
    struct point point;
    struct list* next;
};

FILE *file;



double angleBtwP(struct point* d, struct point* e, struct point* f){
    struct point a, b;

    a.x = e->x - d->x;
    a.y = e->y - d->y;
    b.x = f->x - e->x;
    b.y = f->y - e->y;

    return (a.x*b.y) - (b.x*a.y);
}

int doIntersect(struct point* p00, struct point* p01, struct point* p10, struct point* p11){
    int p0 = (int)angleBtwP(p00, p01, p10);
    int p1 = (int)angleBtwP(p00, p01, p11);
    int p2 = (int)angleBtwP(p10, p11, p00);
    int p3 = (int)angleBtwP(p10, p11, p01);

    if((p0 ^ p1) < 0 && (p2 ^ p3) < 0 && p2 != p3 && p0 != p1){
        return 1;
    }
    return 0;
}

int InPoly(struct list* poly,struct point* p, int minX, int maxX){
    int i;
    struct point temp;
    struct list* itter = poly;
    int CountClock = 0;
    int Clock = 0;
    temp.y = p->y;
    temp.x = maxX;

    while(itter->next){
        if(doIntersect(p, &temp, &itter->point, &itter->next->point)){
            CountClock = 1;
            break;
        }
        itter = itter->next;
    }

    itter = poly;
    temp.x = minX;
    while(itter->next){
        if(doIntersect(p, &temp, &itter->point, &itter->next->point)){
            Clock = 1;
            break;
        }
        itter = itter->next;
    }

    if(Clock == CountClock && Clock != 0){
        return 1;
    }else return 0;
}

struct list* push(){
    struct list* temp;
    temp = malloc(sizeof(struct list));
    if(temp == NULL) exit(EXIT_FAILURE);
    temp->next = NULL;
    return temp;
}
void jarvis(struct pointsArr* input, struct list* polygon, int minNum){
    double temp;
    int index, i, n, l, q, j;
    struct list* itter = polygon->next;

    n = input->len;
    index = minNum;
    l = index;
    j = 1;
    while(1){
        q = (l + 1) % n;
        for(i = 0; i < n; i++){
            if(i == l) continue;
            temp = angleBtwP(&input->ptr[l], &input->ptr[i], &input->ptr[q]);
            if(temp > 0 || temp == 0) {
                q = i;
            }
        }
        l = q;
        if(l == index){
            break;
        }

        itter->next = push();
        itter = itter->next;
        itter->point.x = input->ptr[q].x;
        itter->point.y = input->ptr[q].y;
        j++;
    }
    itter->next = push();
    itter = itter->next;
    itter->point.x = polygon->point.x;
    itter->point.y = polygon->point.y;
}



struct list* calcPoly(struct pointsArr* input){
    int i, minNum;
    struct point left;
    double temp;
    double min = input->ptr[0].y;
    struct list* const Poly = malloc(sizeof(struct list));
    struct list* itter;
    for(i = 1; i < input->len; i++){
        if(input->ptr[i].y < min){
            min = input->ptr[i].y;
            minNum = i;
        }
    }
    Poly->next = push();
    itter = Poly->next;
    min = 3.15;
    left.x = input->ptr[minNum].x - 1;
    left.y = input->ptr[minNum].y;
    Poly->point.x = input->ptr[minNum].x;
    Poly->point.y = input->ptr[minNum].y;

    for(i = 0; i < input->len; i++){
        if(i == minNum) continue;
        temp = angleBtwP(&left, &input->ptr[minNum], &input->ptr[i]);
        if(temp < min && temp >= 0){
        itter->point.x = input->ptr[i].x;
        itter->point.y = input->ptr[i].y;
        min = temp;
        }
    }

    jarvis(input, Poly, minNum);

//    printf("/////// POLY ////////\n");
//
//
//    itter = Poly;
//    while(itter){
//        printf("(%lf, %lf)\n", itter->point.x, itter->point.y);
//        itter = itter->next;
//    }
    return Poly;
}



int main(){
    struct pointsArr points;
    struct list* poly, *itter, *next;
    struct point check;
    int i;
    file = fopen("points", "rb");

    if(file == NULL){
        return 1;
    }

    fread(&points.len, sizeof(int), 1, file);
    fread(points.min, sizeof(int), 2, file);
    fread(points.max, sizeof(int), 2, file);

    points.ptr = (struct point*)malloc(points.len*sizeof(struct point));
    if(points.ptr == NULL)return 2;
    fread(points.ptr, sizeof(struct point), points.len, file);

    printf("There is %d points in (%d; %d) (%d; %d) range\n", points.len, points.min[0], points.min[1], points.max[0], points.max[1]);

    for(i = 0; i < points.len; i++){
        printf("%lf %lf\n", points.ptr[i].x, points.ptr[i].y);
    }
    poly = calcPoly(&points);
    itter = poly;
    printf("Polygon:\n");
    while(itter){
        printf("%lf %lf\n", itter->point.x, itter->point.y);
        itter = itter->next;
    }

    printf("Point for test:\n");
    scanf("%lf %lf", &check.x, &check.y);

    if(InPoly(poly, &check, points.min[0], points.max[0])){
        printf("\nYes\n");
    }else{
        printf("\nNo\n");
    }

    fclose(file);
    free(points.ptr);
    itter = poly;
    while(itter){
        next = itter->next;
        free(itter);
        itter = next;
    }
}