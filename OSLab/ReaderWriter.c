#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Shared Data
int data = 0;
int read_count = 0;

// Semaphores
sem_t mutex;       // Protects read_count
sem_t write_block; // Blocks writers when readers are present (and vice versa)

// Writer Thread
void* writer(void* arg) {
    int id = *((int*)arg);
    free(arg); // Clean up memory

    printf("[Writer %d] Waiting to write...\n", id);

    // 1. Request exclusive access
    sem_wait(&write_block); 

    // 2. Critical Section (Writing)
    printf("[Writer %d] Writing data...\n", id);
    sleep(1); // Simulate writing time
    data++;
    printf("[Writer %d] Updated data to %d\n", id, data);

    // 3. Release access
    sem_post(&write_block); 

    return NULL;
}

// Reader Thread
void* reader(void* arg) {
    int id = *((int*)arg);
    free(arg); 

    printf("[Reader %d] Waiting to read...\n", id);

    // 1. Entry Section (Update headcount)
    sem_wait(&mutex); // Lock read_count
    read_count++;
    if (read_count == 1) {
        // If I am the FIRST reader, I must lock out writers
        sem_wait(&write_block); 
    }
    sem_post(&mutex); // Unlock read_count

    // 2. Critical Section (Reading)
    // Multiple readers can be here simultaneously because they released 'mutex'
    printf("[Reader %d] Reading data: %d\n", id, data);
    sleep(1); // Simulate reading time

    // 3. Exit Section (Update headcount)
    sem_wait(&mutex); // Lock read_count
    read_count--;
    if (read_count == 0) {
        // If I am the LAST reader, I must unlock writers
        sem_post(&write_block);
    }
    sem_post(&mutex); // Unlock read_count

    return NULL;
}

int main() {
    pthread_t r1, r2, r3, w1, w2;
    
    // Initialize Semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&write_block, 0, 1);

    // Create threads
    int *id;

    // Create Reader 1
    id = malloc(sizeof(int)); *id = 1;
    pthread_create(&r1, NULL, reader, id);

    // Create Reader 2
    id = malloc(sizeof(int)); *id = 2;
    pthread_create(&r2, NULL, reader, id);

    // Create Writer 1
    id = malloc(sizeof(int)); *id = 1;
    pthread_create(&w1, NULL, writer, id);

    // Create Reader 3
    id = malloc(sizeof(int)); *id = 3;
    pthread_create(&r3, NULL, reader, id);

    // Wait for everyone to finish
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);
    pthread_join(r3, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&write_block);

    return 0;
}