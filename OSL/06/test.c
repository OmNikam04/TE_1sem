#include <stdio.h>
#include <string.h>

void printAnswer(int rows, int cols, int ans[][cols], int hits, int miss) {
    for (int i = 0; i < rows; i++) {
        printf("f%d ", i + 1);
        for (int j = 0; j < cols; j++) {
            if (ans[i][j] == -1) {
                printf("* ");
            } else {
                printf("%d ", ans[i][j]);
            }
        }
        printf("\n");
    }

    printf("---------------------------------------\n");
    printf("Total hits: %d\n", hits);
    printf("Total miss: %d\n", miss);
}

int findLRUIndex(int queue[], int recentlyUsed[], int frames) {
    int lruIndex = 0;
    for (int i = 0; i < frames; i++) {
        if (recentlyUsed[i] < recentlyUsed[lruIndex]) {
            lruIndex = i;
        }
    }
    return lruIndex;
}

void lru_solution(int process[], int queue[], int frames, int n) {
    memset(queue, -1, frames * sizeof(int));
    int ans2[frames][n];
    int hit = 0, miss = 0, col = 0;
    int recentlyUsed[frames];
    memset(recentlyUsed, -1, frames * sizeof(int));

    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < frames; j++) {
            if (process[i] == queue[j]) {
                flag = 1;
                recentlyUsed[j] = i; // Update recently used time
                break;
            }
        }

        if (flag == 1) {
            hit++;
        } else {
            miss++;
            if (col < frames) {
                queue[col] = process[i];
                recentlyUsed[col] = i;
                col++;
            } else {
                int lruIndex = findLRUIndex(queue, recentlyUsed, frames);
                queue[lruIndex] = process[i];
                recentlyUsed[lruIndex] = i;
            }
        }

        for (int row = 0; row < frames; row++) {
            ans2[row][col] = queue[row];
        }
    }

    printAnswer(frames, n, ans2, hit, miss);
}

int main() {
    int n = 15; // Replace with the actual number of pages
    int process[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5, 6, 7, 8}; // Replace with your page reference string
    int frames = 4; // Replace with the number of frames you want

    int queue[frames];

    lru_solution(process, queue, frames, n);

    return 0;
}
