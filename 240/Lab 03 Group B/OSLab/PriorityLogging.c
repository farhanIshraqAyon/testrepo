#include <stdio.h>
#include <pthread.h>

// 1. Define the Mutex and Shared Resource
// Using PTHREAD_MUTEX_INITIALIZER as shown in the manual [cite: 78]
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int high_done_count = 0; // Shared resource to track high priority completion

// 2. High Priority Function
void* high_priority_task(void* arg) {
    // Acquire lock to enter critical section [cite: 95]
    pthread_mutex_lock(&lock);

    // Critical Section: Print and update state 
    printf("[HIGH] %s\n", (char*)arg);
    high_done_count++;

    // Release lock [cite: 97]
    pthread_mutex_unlock(&lock);
    return NULL;
}

// 3. Low Priority Function
void* low_priority_task(void* arg) {
    while (1) {
        // Acquire lock to check shared state safely [cite: 95]
        pthread_mutex_lock(&lock);

        // Check if High priority threads (Total 2) are finished
        if (high_done_count >= 2) {
            printf("[LOW] %s\n", (char*)arg);
            pthread_mutex_unlock(&lock); // Release before breaking [cite: 97]
            break; // Exit loop
        }

        // If not ready, release lock and retry [cite: 97]
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    // Declare thread handles [cite: 56]
    pthread_t t1, t2, t3, t4;

    // Create threads. Note: We pass the message as the 4th argument.
    // The PDF creates threads using NULL attributes and NULL args[cite: 58], 
    // but here we pass the string message to the function.

    // Thread 1 (Low): "Network OK"
    pthread_create(&t1, NULL, low_priority_task, "Network OK");

    // Thread 2 (High): "Disk Failure"
    pthread_create(&t2, NULL, high_priority_task, "Disk Failure");

    // Thread 3 (Low): "User Login"
    pthread_create(&t3, NULL, low_priority_task, "User Login");

    // Thread 4 (High): "Power Surge"
    pthread_create(&t4, NULL, high_priority_task, "Power Surge");

    // Wait for all threads to finish execution [cite: 68, 71]
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    return 0;
}