#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct matrixd_ {
    double **ptr;
    int COLLS;
    int ROWS;
};

struct matrixd_ allocMatrix(int COLLS,int ROWS);
void freeMat(struct matrixd_ *input);
void printfMat(struct matrixd_ *a);
struct matrixd_ CpMatrix(struct matrixd_ *input);
double *Gauss(struct matrixd_ *input);
int checkVal(double* results, struct matrixd_ *input);
struct matrixd_ readFromFile(const char * __filename);


int main() {

    int i, j;
    double *res;
    struct matrixd_ matrix, copy;

    matrix = readFromFile("l7v03.txt");
    if(matrix.COLLS-matrix.ROWS != 1)printf("It seems that your matrix isn't squared, so result will be incorrect :(\n");

    printfMat(&matrix);
    copy = CpMatrix(&matrix);
    printfMat(&copy);
    res = Gauss(&matrix);


    if(!checkVal(res, &copy)){
        printf("Results:\n");
        for (i = 0; i < matrix.ROWS; i++) {
            printf("X%d = %lf\n", i, res[i]);
        }
    }else{
        printf("Matrix is not consistent\n");
    }

    free(res);
    freeMat(&matrix);
    freeMat(&copy);

    return 0;
}


struct matrixd_ allocMatrix(int COLLS,int ROWS) {
    struct matrixd_ a;
    int i;

    a.COLLS = COLLS;
    a.ROWS = ROWS;
    a.ptr = calloc(COLLS, sizeof(double));
    for (i = 0; i < COLLS; i++) {
        a.ptr[i] = calloc(ROWS, sizeof(double));
        memset(a.ptr[i], 0, ROWS);
        if (a.ptr[i] == NULL) {
            printf("There is an error in matrix allocation\n");
        }
    }
    return a;
}

void freeMat(struct matrixd_ *input){
    int i;
    for(i = 0; i < input->COLLS; i++){
        free(input->ptr[i]);
    }
    free(input->ptr);
}

void printfMat(struct matrixd_ *a) {
    int i, j;

    if(a->COLLS == 0 || a->ROWS == 0){
        printf("There is an error marked matrix or it wasn't allocated propertly\n");
        return;
    }

    for (i = 0; i < a->ROWS; i++) {
        for (j = 0; j < a->COLLS; j++) {
            printf("%lf ", a->ptr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}



struct matrixd_ CpMatrix(struct matrixd_ *input) {
    int i;
    struct matrixd_ out = allocMatrix(input->COLLS, input->ROWS);

    for (i = 0; i < input->ROWS; i++) {
        memcpy(out.ptr[i], input->ptr[i], (size_t) sizeof(double) * (input->COLLS));
    }
    return out;
}

double *Gauss(struct matrixd_ *input) {
    int n = input->ROWS;
    int i, k, maxRow;
    double *x;
    double c, tmp, maxEl;


    for (i = 0; i < n; i++) {
        maxEl = fabs(input->ptr[i][i]);
        maxRow = i;
        for (k = i + 1; k < n; k++) {
            if (fabs(input->ptr[k][i]) > maxEl) {
                maxEl = fabs(input->ptr[k][i]);
                maxRow = k;
            }
        }

        for (k = i; k < n + 1; k++) {
            tmp = input->ptr[maxRow][k];
            input->ptr[maxRow][k] = input->ptr[i][k];
            input->ptr[i][k] = tmp;
        }


        for (k = i + 1; k < n; k++) {
            c = -input->ptr[k][i] / input->ptr[i][i];
            for (int j = i; j < n + 1; j++) {
                if (i == j) {
                    input->ptr[k][j] = 0;
                } else {
                    input->ptr[k][j] += c * input->ptr[i][j];
                }
            }
        }
    }


    x = calloc(input->ROWS, sizeof(double));
    for (i = n - 1; i >= 0; i--) {
        x[i] = input->ptr[i][n] / input->ptr[i][i];
        for (k = i - 1; k >= 0; k--) {
            input->ptr[k][n] -= input->ptr[k][i] * x[i];
        }
    }
    return x;
}


int checkVal(double* results, struct matrixd_ *input){
    int i, j;
    double sum;
    const double eps = 1e-5;
    for(i = 0; i < input->COLLS-1; i++){
        sum = 0;
        for(j = 0; j < input->ROWS; j++) {
            sum += results[j] * input->ptr[i][j];
        }
        if(fabs(sum - input->ptr[i][input->COLLS-1]) > eps) return 1;
    }
    return 0;
}

struct matrixd_ readFromFile(const char * filename){
    int count = 0;
    int COLLS = 1;
    int ROWS = 1;
    int i, j;

    struct matrixd_ matrix;

    int c;
    int prev = 0;

    FILE *datafile;
    datafile = fopen(filename, "r");

    if(datafile == NULL){
        printf("ERROR in opening file for matrix\n");
        matrix.COLLS = 0;
        matrix.ROWS = 0;
        return matrix;
    }

    c = getc(datafile);

    while(c != EOF){

        count++;
        if(count > 1e5){
            printf("It seems like strange activity or too large file\n");
            break;
        }

        if(c == 10 && prev != 10 && prev != 32){
            ROWS++;
        }
     //   if(prev == 10 && c != 10) COLLS = 1;

        if(c == 32 && prev != 32 && ROWS == 1) COLLS++;


        prev = c;
        c = getc(datafile);
    }
    ROWS--;
    matrix = allocMatrix(COLLS, ROWS);

    fseek(datafile, 0l, SEEK_SET);

    for (i = 0; i < matrix.ROWS; i++) {
        for (j = 0; j < matrix.COLLS; j++) {
            fscanf(datafile, "%lf", &matrix.ptr[i][j]);
        }
    }

    fclose(datafile);
    return matrix;

}