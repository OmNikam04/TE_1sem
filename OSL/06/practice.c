#include <stdio.h>
#include <string.h>

void printAnswer(int rows, int cols, int ans[][cols], int hits, int miss)
{

    for (int i = 0; i < rows; i++)
    {
        printf("f%d ", i + 1);
        for (int j = 0; j < cols; j++)
        {
            if (ans[i][j] == -1)
            {
                printf("* ");
            }
            else
            {
                printf("%d ", ans[i][j]);
            }
        }
        printf("\n");
    }

    printf("---------------------------------------\n");
    printf("Total hits: %d\n", hits);
    printf("Total miss: %d\n", miss);
}

void FIFO(int *process, int *queue, int frames, int n)
{

    int index = 0, miss = 0, hit = 0, col = 0;
    int ans1[frames][n];
    for (int i = 0; i < n; i++)
    {
        // todo 1. check if page is present in queue or not

        // flag = 1 Means page fault occured
        int flag = 0;
        for (int j = 0; j < frames; j++)
        {
            if (process[i] == queue[j])
            {
                flag = 1;
                break;
            }
        }

        // todo: 2. If page fault is not occured then miss++ and add the new process to queue
        if (flag == 0)
        {
            queue[index] = process[i];
            index = (index + 1) % frames;
            miss++;
        }
        // todo: 3. If page fault is occured then hit++
        else
        {
            hit++;
        }
        // todo: 4. Store the entire queue into 2d answer array
        for (int row = 0; row < frames; row++)
        {
            ans1[row][col] = queue[row];
        }
        col++;
    }

    // todo: 5. Print the 2d answer array if element is -1 then * else print element
    printAnswer(frames, n, ans1, hit, miss);
}

int predict(int *process, int *queue, int frames, int n, int index)
{

    int res = -1, farthest = index;
    for (int i = 0; i < frames; i++)
    {
        int j;
        for (j = index; j < n; j++)
        {
            if (queue[i] == process[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        // if page is never reference in future, return it
        if (j == n)
        {
            return i;
        }
    }

    // if all of the frames were not in future,
    // return any of them, we return0. Otherwise
    // return res
    return (res == -1) ? 0 : res;
}

// hit means memory needs a page and that page already in memory

void optimal_solution(int *process, int *queue, int frames, int n)
{
    memset(queue, -1, frames * sizeof(int));
    int ans2[frames][n];
    int hit = 0, miss = 0, col = 0, index = 0;
    for (int i = 0; i < n; i++)
    {
        // flag 1 means page fault not occured
        int flag = 0;
        for (int j = 0; j < frames; j++)
        {
            if (process[i] == queue[j])
            {
                flag = 1;
                break;
            }
        }

        if (flag == 1)
        {
            hit++;
        }
        else
        {
            miss++;
            // if space is available in queue then insert the page
            if (index < frames)
            {
                queue[index++] = process[i];
            }
            // find the page to be replaced
            else
            {
                int j = predict(process, queue, frames, n, i + 1);
                queue[j] = process[i];
            }
        }
        for (int row = 0; row < frames; row++)
        {
            ans2[row][col] = queue[row];
        }
        col++;
    }

    printAnswer(frames, n, ans2, hit, miss);
}

int find_least_used(int *process, int *queue, int frames, int n, int index)
{
    
    int res = -1, farthest = index;
    for (int i = 0; i < frames; i++)
    {
        int j;
        for (j = index; j >=0; j--)
        {
            if (queue[i] == process[j])
            {
                if (j < farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        // if page is never reference in past, return it
        if (j == n)
        {
            return i;
        }
    }

    // if all of the frames were not in past,
    // return any of them, we return 0. Otherwise
    // return res
    return (res == -1) ? 0 : res;
}

void LRU(int *process, int *queue, int frames, int n){

    int index = 0, hit = 0, miss = 0, col = 0;
    int ans3[frames][n];
    memset(queue, -1, frames * sizeof(int));

    for(int i =0; i<n; i++){
        //todo: Check if page fault has occured; flag = 1 means page fault
        int flag = 0;
        for(int j =0 ; j<frames; j++){
            if(process[i] == queue[j]){
                flag = 1;
                break;
            }
        }

        if(flag == 1){
            hit++;
        }
        else{
            miss++;

            if(index < frames){
                queue[index++] = process[i];
            }
            // find least recently used page to be replaced
            else{
                int j = find_least_used(process, queue, frames, n, i-1);
                queue[j] = process[i];
            }
        }

        for(int row = 0; row < frames; row++){
            ans3[row][col] = queue[row];
        }
        col++;
    }

    printAnswer(frames, n, ans3, hit, miss);
}

int main()
{
    int n;
    printf("Enter the lenght of string: ");
    scanf("%d", &n);
    int process[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &process[i]);

    int frames;
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // creating queue for storing the pages
    int queue[frames];
    memset(queue, -1, frames * sizeof(int));

    // FIFO(process, queue, frames, n);
    // optimal_solution(process, queue, frames, n);
    LRU(process, queue, frames, n);
}