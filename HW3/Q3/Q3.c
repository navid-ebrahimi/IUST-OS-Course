// Reference: https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


#define THINKING 2
#define HUNGRY 1
#define EATING 0

int state[5];
int philosopher_id[5];

sem_t semaphore;
sem_t signals[5];

void test(int i)
{
	if (
		state[(i + 4) % 5] != EATING
		&& state[i] == HUNGRY
		&& state[(i + 1) % 5] != EATING) 
		{
		state[i] = EATING;
		sleep(1);
		printf("Philosopher %d pickes up %d and %d\n", i + 1, (i + 4) % 5 + 1, i + 1);
		printf("Philosopher %d is Eating\n", i + 1);
		sem_post(&signals[i]);
	}
}

void take_fork(int i)
{
	sem_wait(&semaphore);
	state[i] = HUNGRY;
	printf("Philosopher %d is Hungry\n", i + 1);
	test(i);
	sem_post(&semaphore);
	sem_wait(&signals[i]);
	sleep(1);
}

void put_fork(int i)
{
	sem_wait(&semaphore);
	state[i] = THINKING;
	printf("Philosopher %d putting %d and %d down\n", i + 1, (i + 4) % 5 + 1, i + 1);
	printf("Philosopher %d is thinking\n", i + 1);
	test((i + 4) % 5);
	test((i + 1) % 5);
	sem_post(&semaphore);
}

void* philosopher(void* phnum)
{
	while (1) {
		int* i = phnum;
		sleep(1);
		take_fork(*i);
		sleep(1);
		put_fork(*i);
	}
}

int main()
{
	for (int i = 0; i < 5; i++)
		philosopher_id[i] =	i;
	int i;
	pthread_t tid[5];
	sem_init(&semaphore, 0, 1);
	for (i = 0; i < 5; i++)
		sem_init(&signals[i], 0, 0);
	for (i = 0; i < 5; i++) 
	{
		printf("Philosopher %d is thinking\n", i + 1);
		pthread_create(&tid[i], NULL, philosopher, &philosopher_id[i]);
	}
	for (i = 0; i < 5; i++)
		pthread_join(tid[i], NULL);
}
