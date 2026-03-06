#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Global definitions
sem_t lock;      // Binary semaphore acting as a mutex
sem_t sem_h;     // Queue for Hydrogen atoms
sem_t sem_o;     // Queue for Oxygen atoms

int h_count = 0; // Waiting Hydrogen atoms
int o_count = 0; // Waiting Oxygen atoms

// Hydrogen Thread
void* h_ready(void* arg) {
    printf("H Ready\n");
    
    // 1. Acquire Lock (Enter Critical Section)
    sem_wait(&lock);
    h_count++;
    
    // 2. Check if a Bond can be formed (2 H + 1 O)
    // Since we are an H, we need at least one OTHER H (count >= 2) and one O.
    if (h_count >= 2 && o_count >= 1) {
        // Captain Mode: We are the last piece needed.
        
        // Release one waiting H (the partner H)
        sem_post(&sem_h);
        
        // Release one waiting O
        sem_post(&sem_o);
        
        // Update counters for the bonded group
        h_count -= 2;
        o_count -= 1;
        
        printf("Bond Formed!\n");
        
        // Release Lock
        sem_post(&lock);
    } else {
        // Passenger Mode: Not enough atoms yet.
        
        // Release Lock so others can enter
        sem_post(&lock);
        
        // Wait in the Hydrogen queue
        sem_wait(&sem_h);
    }
    
    return NULL;
}

// Oxygen Thread
void* o_ready(void* arg) {
    printf("O Ready\n");
    
    // 1. Acquire Lock (Enter Critical Section)
    sem_wait(&lock);
    o_count++;
    
    // 2. Check if a Bond can be formed
    // Since we are O, we just need two H atoms.
    if (h_count >= 2) {
        // Captain Mode: We are the last piece needed.
        
        // Release two waiting H atoms
        sem_post(&sem_h);
        sem_post(&sem_h);
        
        // Update counters
        h_count -= 2;
        o_count -= 1;
        
        printf("Bond Formed!\n");
        
        // Release Lock
        sem_post(&lock);
    } else {
        // Passenger Mode: Not enough H atoms yet.
        
        // Release Lock
        sem_post(&lock);
        
        // Wait in the Oxygen queue
        sem_wait(&sem_o);
    }
    
    return NULL;
}

int main() {
    // Initialize Semaphores
    // Lock initialized to 1 (Binary Semaphore for mutual exclusion) [cite: 130]
    sem_init(&lock, 0, 1);
    
    // Queues initialized to 0 (Threads block until signaled)
    sem_init(&sem_h, 0, 0);
    sem_init(&sem_o, 0, 0);

    pthread_t threads[12];
    
    // Simulation: Create atoms in a sequence that requires waiting
    // Example: H, H, H, H (waiting) ... then O, O (bonds form)
    printf("--- Creating 4 Hydrogen Atoms ---\n");
    pthread_create(&threads[0], NULL, h_ready, NULL);
    pthread_create(&threads[1], NULL, h_ready, NULL);
    pthread_create(&threads[2], NULL, h_ready, NULL);
    pthread_create(&threads[3], NULL, h_ready, NULL);
    
    sleep(1); // Small delay to visualize the waiting
    
    printf("--- Creating 2 Oxygen Atoms ---\n");
    pthread_create(&threads[4], NULL, o_ready, NULL); // Should form 1st bond
    pthread_create(&threads[5], NULL, o_ready, NULL); // Should form 2nd bond

    // Join all threads
    for (int i = 0; i < 6; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy semaphores [cite: 161]
    sem_destroy(&lock);
    sem_destroy(&sem_h);
    sem_destroy(&sem_o);

    return 0;
}