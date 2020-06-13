#include "stdio.h"
#include <stdlib.h>
typedef struct stack{
    float stack[25];
    int len;
} stack;

int getNext(FILE* file);
void push(stack *a, int el);
void pop(stack *a, int oper);


int main() {
    int end, i = 0;
    stack nums;
    nums.len = 0;
    char name[40];

    printf("Enter file name: ");
    scanf("%s", name);

    FILE* dataFile = fopen(name, "r");
    if(dataFile == NULL){
        printf("Can't find this file :(\n");
        return 21;
    }
    end = getNext(dataFile);
    while(end != -2){
        if(end >= 0){
            push(&nums, end);
        }
        if(end < 0){
            if(end != -1){
                pop(&nums, end);
            }
        }
        printf("%d ", end);
        end = getNext(dataFile);
        i++;
    }
    if(nums.len > 1){
        printf("Syntax error!\n");
    }
    printf("\n");
    for(i = 0; i < nums.len; i++){
        printf("%f ", nums.stack[i]);
    }

    fclose(dataFile);
    return 0;
}

int getNext(FILE* file){
   static int prev;
   int c, t;
   int i;
   int Num = 0, pow = 0;
   static char isClosed = 0;
   int nums[15];
   if(isClosed && (prev == 41 || prev == 93)){
       isClosed = 0;
       return -prev;
   }
   c = getc(file);
    while(c != EOF){
        if(c != 32 && c != 9 && c != 40 && !(c > 47 && c < 58) && (c != 91) && c != 93 && c != 41){
            return -1;
        }
        if((c == 93 || c == 41) && !(prev > 47 && prev < 58)){
            return -c;
        }
        if((prev > 47 && prev < 58) && (!(c > 47 && c < 58))) {
            if(c == 93 || c == 41){
                prev = c;
                isClosed = 1;
            }
            break;
        }
        if(c > 47 && c < 58){
            nums[pow] = c;
            pow++;
        }
        prev = c;
        c = getc(file);
    }
    if(c == EOF) return -2;
    t = pow-1;
    pow = 1;
    for(i = t; i > 0; i--){
        if(nums[i]){
            Num += (nums[i]-48)*pow;
        }else{
            Num += pow;
        }
        pow *= 10;
    }
    if(nums[0]){
        Num += (nums[0]-48)*pow;
    }else{
        Num += pow;
    }

    prev = c;
    return Num;
}
void push(stack *a, int el){
    if(a->len < 25){
        a->stack[(++a->len)-1] = (float)el;
    }else{
        printf("Syntax error!\n");
        exit(EXIT_FAILURE);
    }
}
void pop(stack *a, int oper){
    if(oper == -41){
        a->stack[a->len-2] += a->stack[a->len-1];

    }else if(oper == -93){
        a->stack[a->len-2] = (a->stack[a->len-2]*a->stack[a->len-1])/(a->stack[a->len-2]+a->stack[a->len-1]);
    }else{
        printf("Unsupported operand!\n");
        exit(EXIT_FAILURE);
    }
    if(a->len > 1){
        a->len--;
    }else{
        printf("Syntax error!\n");
        exit(EXIT_FAILURE);
    }

}