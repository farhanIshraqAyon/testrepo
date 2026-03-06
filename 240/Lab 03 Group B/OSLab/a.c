#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Shared Resources (Bank Accounts) [cite: 19]
int A = 1000;
int B = 1000;
int C = 1000;

// Mutexes: One for each account 
pthread_mutex_t lock_A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_B = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_C = PTHREAD_MUTEX_INITIALIZER;

// Thread T1: Transfers 100 from A -> B (10 times)
void* transfer_A_to_B(void* arg) {
    for (int i = 0; i < 10; i++) {
        // Entry Section: Lock involved accounts 
        pthread_mutex_lock(&lock_A);
        pthread_mutex_lock(&lock_B);

        // Critical Section [cite: 10]
        if (A >= 100) {
            A -= 100;
            B += 100;
            printf("T1: Transferred 100 from A to B. (A=%d, B=%d, C=%d)\n", A, B, C);
        } else {
            printf("T1: Insufficient funds in A\n");
        }

        // Exit Section: Unlock accounts 
        pthread_mutex_unlock(&lock_B);
        pthread_mutex_unlock(&lock_A);
    }
    return NULL;
}

// Thread T2: Transfers 50 from B -> C (20 times)
void* transfer_B_to_C(void* arg) {
    for (int i = 0; i < 20; i++) {
        pthread_mutex_lock(&lock_B);
        pthread_mutex_lock(&lock_C);

        // Critical Section
        if (B >= 50) {
            B -= 50;
            C += 50;
            printf("T2: Transferred 50 from B to C. (A=%d, B=%d, C=%d)\n", A, B, C);
        } else {
            printf("T2: Insufficient funds in B\n");
        }

        pthread_mutex_unlock(&lock_C);
        pthread_mutex_unlock(&lock_B);
    }
    return NULL;
}

// Thread T3: Transfers 25 from C -> A (40 times)
void* transfer_C_to_A(void* arg) {
    for (int i = 0; i < 40; i++) {
        // Note: In complex systems, we lock in a specific order (e.g., A then C) to avoid deadlock.
        // For this lab exercise, we lock Source then Dest.
        pthread_mutex_lock(&lock_A);
        pthread_mutex_lock(&lock_C);

        // Critical Section
        if (C >= 25) {
            C -= 25;
            A += 25;
            printf("T3: Transferred 25 from C to A. (A=%d, B=%d, C=%d)\n", A, B, C);
        } else {
            printf("T3: Insufficient funds in C\n");
        }

        pthread_mutex_unlock(&lock_C);
        pthread_mutex_unlock(&lock_A);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3; // Declare thread identifiers [cite: 56]

    printf("Initial State: A=%d, B=%d, C=%d\n", A, B, C);

    // Create threads [cite: 58]
    pthread_create(&t1, NULL, transfer_A_to_B, NULL);
    pthread_create(&t2, NULL, transfer_B_to_C, NULL);
    pthread_create(&t3, NULL, transfer_C_to_A, NULL);

    // Wait for threads to finish [cite: 68]
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("--------------------------------------------------\n");
    printf("Final State: A=%d, B=%d, C=%d\n", A, B, C);
    printf("Total Wealth: %d (Invariant check: Should be 3000)\n", A + B + C);

    return 0;
}