#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>


pthread_mutex_t lock;
int arr[1000];
int queue_front = -1;
int queue_back = 0;
int n;
int m;

pthread_t producerid[3];
pthread_t consumerid[3];
int producer_num[3];
int consumer_num[3];


void* produce(void *arg){
    int threadid = *((int*)arg);
    for (int i = 0; i < m; i++){
        while (1){
            pthread_mutex_lock(&lock);
            if (!(queue_front==queue_back || (queue_front==-1 && queue_back == n-1))){
                break;
            }
            pthread_mutex_unlock(&lock);  
        }

        arr[queue_back] = rand();
        printf("Producer Thread %d: Generated numbers %d\n",threadid, arr[queue_back]);
        queue_back = (queue_back + 1) % n;
        pthread_mutex_unlock(&lock);
    }
    
    return NULL;
}



void* consume(void *arg){
    int threadid = *((int*)arg);
    for (int i = 0; i < m; i++){
        while (1){
            pthread_mutex_lock(&lock);
            if ((queue_front + 1) % n != queue_back){
                break;
            }
            pthread_mutex_unlock(&lock);
        }

        queue_front = (queue_front+1) % n;
        int num = arr[queue_front];
        printf("Consumer Thread %d: I got number %d and it is %s\n", threadid, num, num%2==0?"even":"odd");
        pthread_mutex_unlock(&lock);
    }
}


int main(){
    for(int i = 1; i <= 3; i++)
    {
        producer_num[3] = i;
        consumer_num[3] = i;
    }
    srand(time(NULL));

    printf("n: ");
    scanf("%d", &n);
    printf("m: ");
    scanf("%d", &m);

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&producerid[i], NULL, produce, (void*)(&producer_num[i])); 
        pthread_create(&consumerid[i], NULL, consume, (void*)(&consumer_num[i])); 
           
    }
    for (int i = 0; i < 3; i++)
    {
        pthread_join(producerid[i], NULL);
        pthread_join(consumerid[i], NULL);
        
    }

    pthread_mutex_destroy(&lock);
    return 0;
}