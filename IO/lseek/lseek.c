#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    off_t ret = lseek(fd, (off_t) 1825, SEEK_SET);
    if (ret == (off_t) -1) {
        // handle the error
    }

    // set file position of fd to the end of the file
    ret = lseek(fd, 0, SEEK_END);
    if (ret == (off_t) -1) {
        // handle the error
    }

    // find the current file position of the file
    int pos = lseek(fd, 0, SEEK_CUR);
    if (pos == (off_t) -1) {
        // handle the error
    } else {
        // now we have the current file position of the file
    }

    // go beyond the end of the file for 1000bytes:
    ret = lseek(fd, (off_t) 1000, SEEK_END);
    if (ret == (off_t) -1) {
        // handle the error
    }

    return 0;
}