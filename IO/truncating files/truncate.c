#include <stdio.h>
#include <unistd.h>

int main(void) {
    int ret;

    ret = truncate("./text.txt", 5);
    if (ret == -1) {
        perror("truncate");
        return -1;
    }

    return 0;
}