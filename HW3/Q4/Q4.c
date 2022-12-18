#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>


pthread_mutex_t lock;
pthread_cond_t cond1;
int sec_time = 0;
void* clock_alert(void* arg)
{
    int certain_time = *(int*)arg;
    // printf("clock_alert is created\n");
    pthread_mutex_lock(&lock);
    for(int i = 0; i<certain_time; i++)
    {
        printf("time = %d \n", sec_time);
        sec_time++;
        if (sec_time % 10 == 0)
        {
            pthread_cond_wait(&cond1, &lock);
        }
    }
    pthread_mutex_unlock(&lock);
}

void* tik(void* arg)
{
    int certain_time = *(int*)arg;
    // printf("tik is created");
    for(int i = 0; i<certain_time; i++)
    {
        pthread_mutex_lock(&lock);
        printf("Tik %d\n", sec_time);
        sec_time++;
        pthread_cond_signal(&cond1);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
}

int main(int argc, char const *argv[])
{
    int certain_time;
    scanf("%d", &certain_time);
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }
    if (pthread_cond_init(&cond1, NULL) != 0) {
        printf("\n cond init has failed\n");
        return 1;
    }
    printf("certain_time = %d \n", certain_time);
    pthread_t thread1 = 1;
    pthread_t thread2 = 2;
    pthread_create(&thread1, NULL, clock_alert, &certain_time);
    sleep(1);
    pthread_create(&thread2, NULL, tik, &certain_time);
    // printf("thread1 is created\n");
    pthread_join(thread1, NULL);
    // printf("thread1 is joined\n");
    // printf("thread2 is created\n");
    pthread_join(thread2, NULL);
    // printf("thread2 is joined\n");
    return 0;
}
