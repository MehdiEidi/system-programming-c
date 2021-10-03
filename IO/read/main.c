#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>

void nonblockingIO() {
    char buf[BUFSIZ];
    ssize_t nr;

    int fd;
    fd = open("/home/text.txt", O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Couldn't open");
    }

    start:
    nr = read(fd, buf, BUFSIZ);
    if (nr == -1) {
        if (errno == EINTR) {
            goto start;
        }
        if (errno == EAGAIN) {
            // resubmit later
        }
        else {
            // handle error
        }
    }
}

void readAllBytesBlocking() {
    ssize_t ret;
    size_t len;
    unsigned long buf;

    int fd;
    fd = open("/home/text.txt", O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Couldn't open");
    }

    // len should not be greater than ssize_t max size
    if (len > SSIZE_MAX) {
        len = SSIZE_MAX;
    }

    while (len != 0 && (ret = read(fd, &buf, len)) != 0) {
        if (ret == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("read");
            break;
        }

        len -= ret;
        buf += ret;
    }
}