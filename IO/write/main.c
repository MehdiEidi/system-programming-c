#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

int main(void) {
    const char *buf = "Some fancy words!";
    ssize_t ret;
    size_t len;

    int fd;
    fd = open("/home/text.txt", O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Couldn't open");
    }

    while (len != 0 && (ret = write(fd, buf, len)) != 0) {
        if (ret == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("write");
            break;
        }

        len -= ret;
        buf += ret;
    }

    return EXIT_SUCCESS;
}