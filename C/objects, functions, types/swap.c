#include <stdio.h>

void swap1(int, int);
void swap2(int*, int*);

int main(void) {
    int a = 21;
    int b = 17;

    swap2(&a, &b);

    printf("main: a = %d, b = %d\n", a, b);

    return 0;
}

void swap1(int a, int b) {
    int t = a;
    a = b;
    b = t;
    printf("swap1: a = %d, b = %d\n", a, b);
}

void swap2(int *pa, int *pb) {
    int t = *pa;
    *pa = *pb;
    *pb = t;
}