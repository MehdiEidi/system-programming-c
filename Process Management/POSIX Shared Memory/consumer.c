#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void) {
    const int SIZE = 4096;
    const char *name = "OS";

    int fd = shm_open(name, O_RDWR, 0666);

    char *ptr = (char *) mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED,fd, 0);

    printf("%s\n", (char *)ptr);

    shm_unlink(name);

    return EXIT_SUCCESS;
}