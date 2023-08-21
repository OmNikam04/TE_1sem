#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
// 0 1 2 3 4
// 2 3 4 5 5

void merge(int *a, int n, int low, int mid, int high)
{

    int temp[high - low];
    int i = low, j = mid + 1;

    while (i <= mid && j <= high)
    {
        if (a[i] <= a[j])
        {
            temp[i] = a[i];
            i++;
        }
        else
        {
            temp[j] = a[j];
            j++;
        }
    }

    while (i <= mid)
    {
        temp[i] = a[i];
        i++;
    }

    while (j <= high)
    {
        temp[j] = a[j];
        j++;
    }

    // copying temp into original array
    for (int i = low; i <= high; i++)
    {
        a[i] = temp[i];
    }
}
void merge_sort(int *a, int n, int low, int high)
{
    if (low >= high)
        return;
    int mid = (low + high) / 2;
    merge_sort(a, n, low, mid);
    merge_sort(a, n, mid + 1, high);
    merge(a, n, low, mid, high);
}

int main(int argc, char *argv[])
{
    int n = 8;
    int a[8] = {5, 8, 2, 3, 10, 22, 1, 9};

    merge_sort(a, n, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("%d\t", a[i]);
    }
    printf("\n");
    return 0;
}