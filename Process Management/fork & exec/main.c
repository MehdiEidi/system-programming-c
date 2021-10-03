#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        execlp("/bin/ls", "ls", NULL);
    } else {
        printf("Parent Waiting...\n");
        wait(NULL);
        printf("Child Completed\n");
    }

    return EXIT_SUCCESS;
}