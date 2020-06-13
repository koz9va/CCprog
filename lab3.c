//
// Created by Серафим Гончаров on 2/20/20.
//
#include <stdio.h>
#define log2 0.693147180559945

float macheps(){
    float e = 1.0f;
    while(1.0f + e / 2.0f > 1.0f) e /= 2.0f;
    return e;
}

int main(){

    float first[5] = {0};
    long double second[5] = {0};
    long double err[5] = {0};
    float add[4] = {0};
    float adderr[4] = {0};
    float series[4] = {0};
    float serieserr[4] = {0};
    int i;
    float pow_1 = 1;
    float part0 = 0;
    float part1 = 0;


    first[0] = 1/(float)3;
    first[1] = 1/(float)33;
    first[2] = 1/(float)333;
    first[3] = 1/(float)3333;
    first[4] = 1/(float)33333;

    second[0] = 1/3.0;
    second[1] = 1/33.0;
    second[2] = 1/333.0;
    second[3] = 1/3333.0;
    second[4] = 1/33333.0;

    for(i = 0; i < 5; i++){
        err[i] = second[i] - (long double)first[i];
    }

    for(i = 0; i < 10; i++){
        add[0] += 0.1f;
    }
    for(i = 0; i < 100; i++){
        add[1] += 0.01f;
    }
    for(i = 0; i < 1e3; i++){
        add[2] += 0.001f;
    }
    for(i = 0; i < 1e6; i++){
        add[3] += 1e-6f;
    }
    for(i = 0; i < 4; i++){
        adderr[i] = 1 - add[i];

    }

    for(i = 1; i <= 1e4; i++){
        series[0] += pow_1*((float)1/(float)i);
        pow_1 *= -1;
    }
  pow_1 = -1;
    for(i = (int)1e4; i >= 1; i--){
        series[1] += pow_1*((float)1/(float)i);
        pow_1 *= -1;
    }
    for(i = 1; i <= 1e3; i++){
        if(i % 2 == 0){
            part1 += (float)1/(float)i;
        }else{
            part0 += (float)1/(float)i;
        }
    }
    series[2] = part0-part1;
    for(i = 1e3; i <= 1; i--){
        if(i % 2 == 0){
            part1 += (float)1/(float)i;
        }else{
            part0 += (float)1/(float)i;
        }
    }
    series[3] = part0 - part1;

    for(i = 0; i < 4; i++){
        serieserr[i] = log2 - series[i];
    }
    float e = macheps();
    return 0;
}
