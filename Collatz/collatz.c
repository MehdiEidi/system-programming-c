#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc <= 1 || argc > 2) {
        printf("invalid input\n");
        return 1;
    }

    int n = atoi(argv[1]);

    if (n < 1) {
        printf("invalid input\n");
        return 1;
    }
    
    int pid = fork();

    if (pid == -1) {
        printf("error - fork failed");
    } else if (pid == 0) {
        while (n != 1) {
            printf("%d, ", n);

            if (n % 2 == 0) {
                n = n / 2;
            } else {
                n = 3 * n + 1;
            }
        }

        printf("1\n");
    } else {
        wait(NULL);
    }

    return 0;
}