#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void) {
    int ret;
    int fd;

    fd = open("./text.txt", O_RDWR);
    if (fd == -1) {
       perror("open");
       return -1;
    }

    ret = truncate("./text.txt", 5);
    if (ret == -1) {
        perror("truncate");
        return -1;
    }

    return 0;
}