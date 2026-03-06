#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Dimensions and Constants
#define SUB_ARRAY_COUNT 4   // Number of threads/sub-arrays
#define D 20                // Dimension size (SUB_ARRAY_DIM)
#define RANGE 10            // Range of values (0 to 9) for the histogram

// Global Variables
// 4D data array: [SUB_ARRAY_COUNT][D][D][D]
int data_array[SUB_ARRAY_COUNT][D][D][D];

// Global Histogram (Shared Resource)
int global_histogram[RANGE] = {0};

// Single Mutex Declaration [cite: 78]
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// Provided Code: Data Initialization
void init_data_array() {
    srand(0);
    for (int i = 0; i < SUB_ARRAY_COUNT; i++) {
        for (int j = 0; j < D; j++) {
            for (int k = 0; k < D; k++) {
                for (int l = 0; l < D; l++) {
                    data_array[i][j][k][l] = rand() % RANGE;
                }
            }
        }
    }
}

// Thread Function
void* thread_task(void* arg) {
    int thread_id = *(int*)arg;
    
    // 1. Compute Local Histogram (No Mutex needed here)
    int local_histogram[RANGE] = {0};
    
    // Iterate through the assigned 3D sub-array
    for (int j = 0; j < D; j++) {
        for (int k = 0; k < D; k++) {
            for (int l = 0; l < D; l++) {
                int value = data_array[thread_id][j][k][l];
                local_histogram[value]++;
            }
        }
    }

    // 2. Critical Section: Merge Local to Global
    // Acquire the single allowed mutex [cite: 95]
    pthread_mutex_lock(&lock);
    
    for (int i = 0; i < RANGE; i++) {
        global_histogram[i] += local_histogram[i];
    }
    
    // Release the mutex [cite: 97]
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    // Initialize Data
    init_data_array();

    pthread_t threads[SUB_ARRAY_COUNT];
    int thread_ids[SUB_ARRAY_COUNT];

    printf("Starting processing with %d threads...\n", SUB_ARRAY_COUNT);

    // Create Threads [cite: 39]
    for (int i = 0; i < SUB_ARRAY_COUNT; i++) {
        thread_ids[i] = i; // Assign index to thread
        if (pthread_create(&threads[i], NULL, thread_task, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Join Threads [cite: 45]
    for (int i = 0; i < SUB_ARRAY_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    // Verification
    long total_count = 0;
    printf("\n--- Global Histogram ---\n");
    for (int i = 0; i < RANGE; i++) {
        printf("Value %d: %d\n", i, global_histogram[i]);
        total_count += global_histogram[i];
    }

    long expected_total = SUB_ARRAY_COUNT * D * D * D;
    printf("\nTotal Count: %ld\n", total_count);
    printf("Expected:    %ld\n", expected_total);

    if (total_count == expected_total) {
        printf("SUCCESS: Histogram count matches total elements.\n");
    } else {
        printf("FAILURE: Data mismatch.\n");
    }

    return 0;
}