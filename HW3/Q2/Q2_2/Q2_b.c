#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

int matrix[2][2] = {
    {1, 2},
    {3, 4}
};

int matrix2[2][2] = {
    {1, 2},
    {3, 4}
};

typedef struct
{
    int i;
    int n;
}
thread_data;


typedef struct
{
    int flag;
    int counter;
    int num_threads;
    sem_t semophore;
}
barrier;

barrier b;


void barrier_init(barrier *b, int num_threads)
{
    b->flag = 0;
    b->counter = 0;
    b->num_threads = num_threads;
    sem_init(&b->semophore, 0, 1);
}

void barrier_wait(barrier *b)
{
    sem_wait(&b->semophore);
    b->counter++;
    if (b->counter == b->num_threads)
    {
        b->flag = 1;
        b->counter = 0;
    }
    sem_post(&b->semophore);
    while (b->flag == 0);
}

void barrier_destroy(barrier *b)
{
    sem_destroy(&b->semophore);
    b->flag = 0;
    b->counter = 0;
}


int power(int x, int y){
    int result = 1;
    for(int i = 0; i < y; i++){
        result *= x;
    }
    return result;
}

void *thread_function(void *arg)
{
    thread_data *data = (thread_data *)arg;
    int i = data->i;
    int n = data->n;
    int row = i / n;
    int col = i % n;
    int sum = 0;
    for(int k = 0; k < n; k++){
        sum += matrix[row][k] * matrix2[k][col];
    }
    barrier_wait(&b);
    matrix2[row][col] = sum;
    return NULL;
}

int main(int argc, char const *argv[])
{
    int n, m;
    n = 2;
    // initial matrix in line 14-17 and 19-22
    // change d of matrix in line 100
    printf("Enter the number of power: ");
    scanf("%d", &m);
    int number = power(n, 2);
    barrier_init(&b, number);
    pthread_t threads[number];
    for(int j = 0; j < m - 1; j++){
        for(int i = 0; i < number; i++){
            thread_data *data = (thread_data *)malloc(sizeof(thread_data));
            data->i = i;
            data->n = n;
            pthread_create(&threads[i], NULL, &thread_function, data);
        }
        for(int i = 0; i < number; i++){
            pthread_join(threads[i], NULL);
        }
        barrier_destroy(&b);
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", matrix2[i][j]);
        printf("\n");
    }
    /* code */
    return 0;
}