#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char** argv) {
    if (argc <= 1 || argc > 2) {
        printf("invalid input - wrong number of parameters\n");
        return 1;
    }

    int n = atoi(argv[1]);

    if (n < 1) {
        printf("invalid input - parameter must be positive\n");
        return 1;
    }
    
    int pid = fork();

    if (pid < 0) {
        perror("error - fork failed\n");
        return errno;
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

        exit(0);
    } else {
        wait(NULL);
    }

    return 0;
}