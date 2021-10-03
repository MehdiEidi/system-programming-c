#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
   int fd1;
   fd1 = open("/home/text.txt", O_WRONLY | O_TRUNC | O_CREAT);
   if (fd1 == 1) {
       // handle error
   }

    // code above is equivalent to this:
    int fd;
    fd = creat("/home/mehdi/test.txt", 0644);
    if (fd == -1) {
        // handle the error
    }

    return EXIT_SUCCESS;
}
