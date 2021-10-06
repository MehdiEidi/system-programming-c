#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
    char writeMessage[BUFFER_SIZE] = "Greetings...";
    char readMessage[BUFFER_SIZE];

    int fd[2];

    pid_t pid;

    if(pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return EXIT_FAILURE;
    }

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork failed");
        return EXIT_FAILURE;
    }

    if (pid > 0) {
        close(fd[READ_END]);
        write(fd[WRITE_END], writeMessage, strlen(writeMessage)+1);
        close(fd[WRITE_END]);
    } else {
        close(fd[WRITE_END]);
        read(fd[READ_END], readMessage, BUFFER_SIZE);
        printf("read %s\n", readMessage);
        close(fd[READ_END]);
    }

    return EXIT_SUCCESS;
}