#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fd = open("/home/mehdi/text.txt", O_WRONLY | O_TRUNC | O_CREAT);
    if (fd == -1) {
        // handle open error
    }

    if (close(fd) == -1) {
        // handle close error
    }

    return 0;
}