#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_CLIENTS 6
#define MAX_CONCURRENT 3

// Synchronization Primitives
sem_t server_limit;         // Semaphore to limit concurrent access [cite: 117]
pthread_mutex_t status_lock; // Mutex to protect the boolean array [cite: 78]

// Shared Resource
bool is_served[NUM_CLIENTS] = {false}; // Tracks which clients are currently being served
bool running = true; // Flag to stop the monitor thread

// Monitor Thread: Prints the status of clients periodically
void* monitor_status(void* arg) {
    while (running) {
        pthread_mutex_lock(&status_lock); // Lock before reading shared array [cite: 95]
        
        // Print status in the requested format: C1=True, C2=False, etc.
        for (int i = 0; i < NUM_CLIENTS; i++) {
            printf("C%d=%s", i + 1, is_served[i] ? "True" : "----");
            if (i < NUM_CLIENTS - 1) {
                printf(", ");
            }
        }
        printf("\n");
        
        pthread_mutex_unlock(&status_lock); // Unlock after reading [cite: 97]
        
        usleep(10000); // Delay 200ms to make console output readable
    }
    return NULL;
}

// Client Thread: Requests access, holds it, then leaves
void* client_thread(void* arg) {
    int id = *((int*)arg);
    free(arg); // Free memory allocated for ID

    // 1. Request access to the server (Decrement Semaphore)
    sem_wait(&server_limit); // Blocks if count is 0 

    // 2. Critical Section (Update Status to True)
    pthread_mutex_lock(&status_lock);
    is_served[id] = true;
    pthread_mutex_unlock(&status_lock);

    // 3. Simulate Transaction (Hold resource for 1 second)
    sleep(1); 

    // 4. Critical Section (Update Status to False)
    pthread_mutex_lock(&status_lock);
    is_served[id] = false;
    pthread_mutex_unlock(&status_lock);

    // 5. Release access (Increment Semaphore)
    sem_post(&server_limit); // Signals waiting threads 
    
    return NULL;
}

int main() {
    pthread_t clients[NUM_CLIENTS];
    pthread_t monitor;

    // Initialize Semaphore to 3 (Max 3 concurrent transactions) 
    sem_init(&server_limit, 0, MAX_CONCURRENT);
    
    // Initialize Mutex [cite: 78]
    pthread_mutex_init(&status_lock, NULL);

    printf("Starting Transaction Server (Max %d concurrent)...\n", MAX_CONCURRENT);

    // Create Monitor Thread
    pthread_create(&monitor, NULL, monitor_status, NULL);

    // Create 6 Client Threads
    for (int i = 0; i < NUM_CLIENTS; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&clients[i], NULL, client_thread, id); // [cite: 58]
    }

    // Wait for all clients to finish
    for (int i = 0; i < NUM_CLIENTS; i++) {
        pthread_join(clients[i], NULL); // [cite: 68]
    }

    // Stop monitor and clean up
    running = false;
    pthread_join(monitor, NULL);
    sem_destroy(&server_limit); // [cite: 161]
    pthread_mutex_destroy(&status_lock);

    printf("All transactions completed.\n");
    return 0;
}