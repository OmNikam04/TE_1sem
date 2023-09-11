#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n;
    printf("Enter the number of integers: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    qsort(arr, n, sizeof(int), compare);

    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        char *args[4];
        args[0] = "./display_reverse"; // Name of the child program
        args[1] = NULL;
        args[2] = NULL;
        args[3] = NULL;

        execve(args[0], args, NULL);
        perror("Execve failed");
        exit(1);
    } else {
        // Parent process
        // Wait for the child process to finish
        int status;
        wait(&status);

        // Pass the sorted array to the child process using command line arguments
        printf("Parent Process: Passing sorted array to child process...\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        printf("Parent process is exiting.\n");
    }

    return 0;
}
