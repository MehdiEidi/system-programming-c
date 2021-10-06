#include <fcntl.h>
#include <stdio.h>

int main(void) {
    int fd = open("/home/mehdi/text.txt", O_WRONLY | O_SYNC);
    if (fd == -1) {
        perror("open");
        return -1;
    }
}