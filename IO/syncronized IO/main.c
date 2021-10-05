#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(void) {
    int fd;
    // open up a file

    // using fsync system call
    int ret = fsync(fd);
    if (ret == -1) {
        // handle error
    }

    // using fdatasync system call
    ret = fdatasync(fd);
    if (ret == -1) {
        // handle error
    }

    // some filesystems dont implement fsync but implement fdatasync. To make sure of a sync IO in such cases:
    if (fsync == -1) {
        if (errno == EINVAL) {
            if (fdatasync(fd) == -1) {
                perror("fdatasync");
            } else {
                perror("fsync");
            }
        }
    }
}