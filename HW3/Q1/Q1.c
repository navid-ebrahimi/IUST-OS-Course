#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


double pi = 0.0;

double odd_or_even(int y)
{
    if (y % 2 == 0)
    {
        return 1;
    }
    return -1;
}

typedef struct
{
    int n;
    int i;
    int number_of_threads;
} sum_of_pi;

pthread_mutex_t lock;

void* compute_sum_of_pi_multithreading(void *vargp)
{
    // printf("Thread is created\n");
    sum_of_pi *data = (sum_of_pi *)vargp;
    int n = data->n;
    int i = data->i;
    int number_of_threads = data->number_of_threads;
    // printf("n = %d, i = %d, number_of_threads = %d\n", n, i, number_of_threads);

    
    double sum_of_sequence = 0.0;
    if (number_of_threads-1 != i)
    {
        // printf("if\n");
        for (int j = i * number_of_threads; j < (i+1) * number_of_threads; j++)
        {
            // printf("sum_of_sequence = %f \n", sum_of_sequence);
            sum_of_sequence += odd_or_even(j) / (2 * j + 1);
        }
    }
    else
    {
        // printf("else\n");
        for (int j = i*number_of_threads; j < n; j++)
        {

            // printf("sum_of_sequence = %f \n", sum_of_sequence);
            sum_of_sequence += odd_or_even(j) / (2 * j + 1);
        }
    }
    pthread_mutex_lock(&lock);
    pi += 4 * sum_of_sequence;
    pthread_mutex_unlock(&lock);
}

int main(int argc, char const *argv[])
{
    int n, number_of_threads;
    printf("Enter the number: ");
    scanf("%d", &n);
    printf("Enter the number of threads: ");
    scanf("%d", &number_of_threads);
    printf("n = %d\n", n);
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }
    pthread_t thread_id[number_of_threads];
    for (int i = 0; i < number_of_threads; i++)
    {
        sum_of_pi *data = (sum_of_pi *)malloc(sizeof(sum_of_pi));
        data->n = n;
        data->i = i;
        data->number_of_threads = number_of_threads;
        pthread_create(&thread_id[i], NULL, compute_sum_of_pi_multithreading, (void *)data);
    }
    for (int i = 0; i < number_of_threads; i++)
    {
        pthread_join(thread_id[i], NULL);
    }
    printf("pi = %lf\n", pi);
    return 0;
}
