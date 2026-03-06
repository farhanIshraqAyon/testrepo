#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 5 // Number of philosophers

pthread_mutex_t forks[N];
pthread_t philosophers[N];

void *philosopher(void* num) {
    int id = *(int*)num;

    while(1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        // Deadlock prevention: The last philosopher picks up forks in reverse order
        if(id == N - 1) {
            // Last philosopher: Right fork then Left fork
            pthread_mutex_lock(&forks[(id + 1) % N]); 
            pthread_mutex_lock(&forks[id]);
        } else {
            // Other philosophers: Left fork then Right fork
            pthread_mutex_lock(&forks[id]);
            pthread_mutex_lock(&forks[(id + 1) % N]);
        }

        printf("Philosopher %d is eating.\n", id);
        sleep(2);

        // Put down forks
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % N]);
        
        printf("Philosopher %d finished eating and put down forks.\n", id);
    }
}

int main() {
    int i, ids[N];

    // Initialize fork mutexes
    for (i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
        ids[i] = i;
    }

    // Create philosopher threads
    for (i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join threads
    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}