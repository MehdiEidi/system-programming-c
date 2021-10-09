#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    char *buf;
    int fd;

    ssize_t ret = pread(fd, buf, (size_t) 10, (off_t) 180);
    if (ret == -1) {
        // handle the error
    }

    return 0;
}