// Merge sort code: https://www.geeksforgeeks.org/c-program-for-merge-sort/

#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h> 
#include <pthread.h>

int m_prim = 0;
int sign = 0;

typedef struct 
{
    int* arr;
    int count_of_sections;
    int start;
    int end;
    int* subArray;
} 
thread_data;

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        if (sign == 0)
        {
            m = m_prim;
            sign++;
        }
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
void extractElements(int srcArray[], int subArray[], int start, int end)
{
    int num = 0;
    for (int i = start; i < end; i++)
    {
        subArray[num] = srcArray[i];
        num++;
    }
}

void replaceElements(int srcArray[], int subArray[], int start, int end)
{
    int num = 0;
    for (int i = start; i < end; i++)
    {
        srcArray[i] = subArray[num];
        num++;
    }
}

void* for_loop_thread(void *arg)
{
    thread_data *args = (thread_data *) arg;
    extractElements(args->arr, args->subArray, args->start, args->end);
    sign=1;
    mergeSort(args->subArray, 0, args->count_of_sections - 1);
    replaceElements(args->arr, args->subArray, args->start, args->end);
}

void* merge_sort_with_thread(int* arr, int size, int count_of_sections)
{
    int number_of_groups = (size)/(count_of_sections);
    for (int i = 0; i < number_of_groups; i++)
    {
        int start = i * count_of_sections, end = (i + 1) * count_of_sections, s_size = end - start;
        int* subArray = (int*)malloc((size+1) * sizeof(int));
        pthread_t tid;
        thread_data data = {arr, count_of_sections, start, end, subArray};
        pthread_create(&tid, NULL, for_loop_thread, &data);
        pthread_join(tid, NULL);
        free(subArray);
    }
    int sum = 0;
    for (int i = 2; i <= number_of_groups; i++)
    {
        sign = 0;
        m_prim += count_of_sections - 1;
        mergeSort(arr, 0, (i) * count_of_sections - 1);
    }
}

int main(int argc, char const *argv[])
{
    int m,n;
    scanf("%d %d", &m, &n);
    
    int* arr = (int*) malloc(m*sizeof(int));
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    merge_sort_with_thread(arr, m, m/n);
    for (int i = 0; i < m; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
