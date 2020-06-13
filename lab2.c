//
// Created by Серафим Гончаров on 2/11/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


FILE* dataf;

void comp(int* input, int len, int* res){
    int i;
    int Min = input[0];
    int Max = input[0];
    for(i = 0; i < len; i++){
        if(input[i] < Min) Min = input[i];
        if(input[i] > Max) Max = input[i];
    }
    res[0] = Min;
    res[1] = Max;
}

float middle(int* input, int len){
    int sum = 0;
    int i;

    for(i = 0;i < len; i++){
        sum += input[i];
    }
    return  sum/len;
}

double quadratic_diff(int *input, int len, float midd){
    double sum = 0;
    int i;

    for(i = 0; i < len; i++){
        sum += (input[i] - midd) * (input[i] - midd);
    }
    return sum/len;
}

void gistogram(int* input, int len, int* out,  int intlen, int* mn){
    int range  = (int)round(((float)mn[1] - (float)mn[0])/(float)intlen);
    int i, j;

    for(i = 0; i < len; i++){
        for(j = 1; j <= intlen; j++){
            if((input[i] >= range*(j-1)) && (input[i] <= range*j)) {
                out[j-1]++;
                break;
            }
        }
    }

}

void printGist(int* gist, int glen, int dmax, int mh){
    int i, j;
    //const int mh = 10;
    float multip;
    int max = gist[0];
    int min = gist[0];
    int* copy = malloc(sizeof(int)*glen);
    int range;

    for(i = 0; i < glen; i++){
        if(max < gist[i]) max = gist[i];
        if(min > gist[i]) min = gist[i];
        copy[i] = gist[i];
        printf("%d ",copy[i]);
    }
    multip = (float)max/(float)mh;
    for(i = 0; i < glen; i++){
        copy[i] /= multip;
        printf("%d ",copy[i]);
    }
    printf("%f\n",multip);

    for(i = max/multip; i > 0; i--){
        printf("%2d ", (int)(i*multip));
        for(j = 0; j < glen; j++){

            if(copy[j]-i >= 0){
                printf("00");
            }else{
                printf("  ");
            }
            printf(" ");

        }
        printf("\n");
    }
    printf(" ");

    range = dmax/glen;

    for(i = 1; i <= glen; i++){
        printf(" %2d", range*i);
    }

}

int main(){
    char c;
    int i;
    int* data;
    int res_comp[2];
    float mid;
    double quad;
    int inter[8] = {0};
    int mult;
    dataf = fopen("input.txt", "r");
    if(dataf == NULL){
        printf("There is an error in opening the file");
        return 1;
    }
    int datal = 1;

    while(1){
        c = getc(dataf);
        if(c == 32)datal++;
        if(c == EOF) break;
    }

    data = malloc(sizeof(int)*datal);
    memset(data, 0 , datal);

    fseek(dataf, 0L, SEEK_SET);

    for(i = 0; i < datal; i++){
        fscanf(dataf, "%d", &data[i]);
    }
    fclose(dataf);

    printf("Enter max height of gistogramm in symbols:\n");
    scanf("%d", &mult);

    comp(data, datal, &res_comp);

    mid  = middle(data, datal);

    quad = quadratic_diff(data, datal, mid);

    printf("min: %d, max: %d,\n middle: %f, quadratic difference: %f\n\n", res_comp[0], res_comp[1], mid, quad);

    gistogram(data, datal, inter, 8, &res_comp);

    printGist(inter, 8, res_comp[1], mult);

    return 0;
}