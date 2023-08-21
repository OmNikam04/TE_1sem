#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    int temp, swapped;
    do {
        swapped = 0;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                // Swap the elements
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }
    } while (swapped);
}

void insertionSort(int arr[], int n) {
    int key, j;
    for (int i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
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

    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("\nChild process (ID: %d) is sorting using Insertion Sort:\n", getpid());
        insertionSort(arr, n);
        printf("Sorted by Child Process: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        // Parent process
        printf("\nParent process (ID: %d) is sorting using Bubble Sort:\n", getpid());
        bubbleSort(arr, n);
        printf("Sorted by Parent Process: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Wait for the child process to finish
        int status;
        wait(&status);

        // Demonstrate the zombie state by waiting for user input
        printf("\nParent process (ID: %d) is waiting...\n", getpid());
        getchar(); // Wait for user input to proceed

        // Demonstrate the orphan state by making the parent sleep
        printf("\nParent process (ID: %d) is sleeping for 5 seconds...\n", getpid());
        sleep(5); // Sleep for 5 seconds

        printf("\nParent process (ID: %d) is exiting.\n", getpid());
    }

    return 0;
}
