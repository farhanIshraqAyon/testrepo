#include <stdio.h>
#include <pthread.h>
#include <semaphore.h> // [cite: 102]
#include <unistd.h>    // For sleep(), usleep() as per prompt

// Declare semaphores
sem_t sem_power;
sem_t sem_comm;

// Thread 1: Power Subsystem (First in strict order)
void* power_thread(void* arg) {
    // Simulate work/initialization delay
    sleep(1); 
    
    // Critical initialization work
    printf("[Power Thread] Power Initialized. Signal sent.\n");
    
    // Signal that power is done [cite: 122]
    sem_post(&sem_power);
    
    return NULL;
}

// Thread 2: Communication Subsystem (Second in strict order)
void* comm_thread(void* arg) {
    printf("[Comm Thread] Waiting for Signal...\n");
    
    // Wait for Power signal [cite: 120]
    sem_wait(&sem_power);
    
    // Simulate work
    usleep(500000); // 500ms delay
    
    printf("[Comm Thread] Communication Initialized. Signal sent.\n");
    
    // Signal that comm is done [cite: 122]
    sem_post(&sem_comm);
    
    return NULL;
}

// Thread 3: Control Subsystem (Last in strict order)
void* control_thread(void* arg) {
    printf("[Control Thread] Waiting for Signal...\n");
    
    // Wait for Communication signal [cite: 120]
    sem_wait(&sem_comm);
    
    // Initialization complete
    printf("[Control Thread] Control System Initialized.\n");
    
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    // Initialize semaphores to 0. 
    // The second argument '0' creates a semaphore shared between threads of a process.
    // The third argument '0' is the initial value, ensuring threads block immediately. [cite: 130]
    sem_init(&sem_power, 0, 0);
    sem_init(&sem_comm, 0, 0);

    // Create threads in random/reverse order to demonstrate robustness
    // Even if Control starts first, it cannot proceed without signals.
    pthread_create(&t3, NULL, control_thread, NULL);
    pthread_create(&t2, NULL, comm_thread, NULL);
    pthread_create(&t1, NULL, power_thread, NULL);

    // Join threads [cite: 45]
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Destroy semaphores [cite: 161]
    sem_destroy(&sem_power);
    sem_destroy(&sem_comm);

    return 0;
} 