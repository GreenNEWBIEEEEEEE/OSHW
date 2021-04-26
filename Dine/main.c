/*
 * main.c
 * Copyleft (ɔ) 2021 greennewbie <adsl53102@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 

#define N 5 
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 
#define LEFT (id + 4) % N 
#define RIGHT (id + 1) % N 

int state[N] = {THINKING, THINKING, THINKING, THINKING, THINKING}; 
int phil[N] = { 0, 1, 2, 3, 4 }; 

sem_t mutex; 
sem_t S[N];  



void eat(int id)
{
    if (state[id] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        printf("Philosopher %d picks up the forks \n", id + 1);
        printf("Philosopher %d is Eating \n", id + 1 );
        state[id] = EATING;
        sleep(2);
        sem_post(&S[id]);
    }
    
}

void pickUpFork(int id) 
{ 
    sem_wait(&mutex);
    state[id] =  HUNGRY;
    printf("Philosopher %d is HUNGRY \n", id + 1);
    eat(id);
    sem_post(&mutex);
    sem_wait(&S[id]);

    sleep(1);
} 

void putDownfork(int id) 
{ 
    sem_wait(&mutex);
    state[id] = THINKING;
    printf("Philosopher %d puts down the forks \n", id + 1);
    eat(LEFT);
    eat(RIGHT);
    sem_post(&mutex);
} 

void* philospher(void* num) 
{ 

	while (1) { 
		int* i = num; 
		sleep(1); 
		pickUpFork(*i); 
		sleep(0); 
		putDownfork(*i); 
	} 
} 

int main() 
{ 

	int i; 
	pthread_t thread_id[N]; 

	sem_init(&mutex, 0, 1); 

	for (i = 0; i < N; i++) 
		sem_init(&S[i], 0, 0); 

	for (i = 0; i < N; i++) { 
		pthread_create(&thread_id[i], NULL, philospher, &phil[i]);
		printf("Philosopher %d is thinking\n", i + 1);
	}

	for (i = 0; i < N; i++) 
		pthread_join(thread_id[i], NULL); 
} 


