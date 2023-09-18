#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <integer1> <integer2> ...\n", argv[0]);
        exit(1);
    }

    printf("Child Process: Displaying sorted array in reverse order...\n");

    // Start from the last argument (sorted integers) and go in reverse order
    for (int i = argc - 1; i > 0; i--) {
        // Convert the string argument back to an integer
        int num = atoi(argv[i]);
        printf("%d ", num);
    }
    printf("\n");

    printf("Child process is exiting.\n");

    return 0;
}
