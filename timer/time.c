#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

void* create_shared_memory(size_t size);
float time_diff(struct timeval *start, struct timeval *end);

int main(int argc, char **argv) {       
    // extract command
    char* cmd[argc-1];
    for (int i = 0; i < argc-1; i++) {
        cmd[i] = argv[i+1];
    }
    
    // establish shared memory
    void* shm = create_shared_memory(256);

    int pid = fork();

    if (pid == -1) {
        printf("Error - fork failed");
    } else if (pid == 0) {
        struct timeval cur;
        gettimeofday(&cur, NULL);
        memcpy(shm, &cur, sizeof(cur));
        execvp(cmd[0], cmd);
    } else {
        struct timeval cur;
        wait(NULL);
        gettimeofday(&cur, NULL);
        printf("\n\nElapsed Time: %f seconds\n", time_diff(shm, &cur));
    }

    return 0;
}

// create_shared_memory creates and returns an in-memory buffer which can be shared.
void* create_shared_memory(size_t size) {
    // shm will be readable and writable
    int prot = PROT_READ | PROT_WRITE;

    // shm will be shared but anonymous, so only parent and child will be able to use it 
    int visibilty = MAP_ANONYMOUS | MAP_SHARED;

    return mmap(NULL, size, prot, visibilty, -1, 0);
}

// time_diff returns the difference of start and end times.
float time_diff(struct timeval *start, struct timeval *end){
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}