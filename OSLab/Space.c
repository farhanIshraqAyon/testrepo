#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Semaphores for synchronization [cite: 117]
sem_t sem_nav;    // Signals that Fuel is ready
sem_t sem_launch; // Signals that Navigation is ready

// Thread 1: Fuel System (Starts First)
void* fuel_system(void* arg) {
    // 1. Perform work
    printf("[Fuel Thread] Fuel system activated. Signal sent.\n");

    // 2. Signal the next stage (Navigation) to proceed
    sem_post(&sem_nav); // Increments sem_nav to 1 
    
    return NULL;
}

// Thread 2: Navigation System (Waits for Fuel)
void* nav_system(void* arg) {
    printf("[Navigation Thread] Waiting for fuel system...\n");
    
    // 1. Wait for Fuel System signal
    sem_wait(&sem_nav); // Blocks if sem_nav is 0 
    
    // 2. Perform work
    printf("[Navigation Thread] Navigation system online. Signal sent.\n");

    // 3. Signal the next stage (Launch) to proceed
    sem_post(&sem_launch); // Increments sem_launch to 1 
    
    return NULL;
}

// Thread 3: Launch System (Waits for Navigation)
void* launch_system(void* arg) {
    printf("[Launch Thread] Waiting for navigation system...\n");
    
    // 1. Wait for Navigation System signal
    sem_wait(&sem_launch); // Blocks if sem_launch is 0 
    
    // 2. Perform work
    printf("[Launch Thread] Launch sequence initiated!\n");
    
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    // Initialize semaphores to 0
    // This ensures threads BLOCK immediately if they try to wait before a signal is sent.
    sem_init(&sem_nav, 0, 0);      // 
    sem_init(&sem_launch, 0, 0);   // 

    // Create threads in REVERSE or RANDOM order to prove synchronization works
    // Even if Launch is created first, it cannot proceed until Navigation is done.
    pthread_create(&t3, NULL, launch_system, NULL); // [cite: 58]
    pthread_create(&t2, NULL, nav_system, NULL);    // [cite: 58]
    pthread_create(&t1, NULL, fuel_system, NULL);   // [cite: 58]

    // Wait for all threads to complete
    pthread_join(t1, NULL); // [cite: 68]
    pthread_join(t2, NULL); // [cite: 68]
    pthread_join(t3, NULL); // [cite: 68]

    // Destroy semaphores
    sem_destroy(&sem_nav);    // [cite: 161]
    sem_destroy(&sem_launch); // [cite: 161]

    return 0;
}