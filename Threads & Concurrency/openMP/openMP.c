#include <omp.h>
#include <stdio.h>

int main(void) {

    // some sequential code here

    #pragma omp parallel
    {
        printf("I am a parallel region.\n");
    }

    // some sequential code here

    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int c[10];

    #pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        c[i] = a[i] + b[i];
    }

    // some sequentail code here

    for (int i = 0; i < 10; i++) {
        printf("c[%d]=%d\n", i, c[i]);
    }    

    return 0;
}