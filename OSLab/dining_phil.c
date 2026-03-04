#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define N 5
pthread_mutex_t forks[N]; // One mutex per fork
sem_t room;               // Counting semaphore (max 4 philosophers)
void *philosopher(void *arg)
{
    int id = *((int *)arg);
    int left = id;
    int right = (id + 1) % N;
    while (1)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);
        // Enter room (limit 4)
        sem_wait(&room);
        // Pick up forks
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);
        printf("Philosopher %d is eating\n", id);
        sleep(2);
        // Put down forks
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
        // Leave room
        sem_post(&room);
    }
    return NULL;
}
int main()
{
    pthread_t phil[N];
    int ids[N];
    // Initialize room semaphore to 4
    sem_init(&room, 0, 4);
    // Initialize fork mutexes
    for (int i = 0; i < N; i++)
        pthread_mutex_init(&forks[i], NULL);
    for (int i = 0; i < N; i++)
    {
        ids[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++)
        pthread_join(phil[i], NULL);
    return 0;
}