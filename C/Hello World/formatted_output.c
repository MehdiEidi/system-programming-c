#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("%s\n", "Hello World");

    // with error handling
    if (printf("%s\n", "hello world") < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}