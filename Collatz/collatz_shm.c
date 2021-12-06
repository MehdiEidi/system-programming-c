#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>  
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>  
#include <sys/mman.h>  

int main(int argc, char **argv) {
    if (argc <= 1 || argc > 2) {
        printf("invalid input - wrong number of parameters\n");
        return 1;
    }

    int n = atoi(argv[1]);

    if (n < 1) {
        printf("invalid input - parameter must be positive\n");
        return 1;
    }

    const char *shm_name = "shm";
    
    // create shared memory
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0) {
        perror("error - shm_open failed\n");
        return errno;
    }

    // set the size of the shm
    if (ftruncate(shm_fd, 200 * sizeof(int)) == -1) {
        perror("error - ftruncate failed\n");
        shm_unlink(shm_name);
        return errno;
    }

    pid_t pid = fork();
    
    if (pid < 0) {
        perror("error - fork failed\n");
        return errno;
    } else if (pid == 0) {  
        // memory map the shm to the child process's address space
        int *ptr = (int*) mmap(0, 200 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

        if (ptr == MAP_FAILED) {
            perror("error - mmap failed");
            return errno;
        }

        while (n != 1) {
            *ptr = n;
            ptr++;

            if (n % 2 == 0) {
                n /= 2;
            } else {
                n = n * 3 + 1;
            }
        }

        *ptr = n;
        
        exit(0);
    } else {
        wait(NULL);

        // memory map the shm to the parent process's address space
        int *ptr = (int*) mmap(0, 200 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

        while (*ptr != 1) {
            printf("%d, ", *ptr);
            ptr++;
        }
        printf("1\n");

        shm_unlink(shm_name);
    }

    return 0;
}
