#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
int *active_config = NULL;
pthread_mutex_t config_mutex = PTHREAD_MUTEX_INITIALIZER;
void *reader(void *arg)
{
    int id = *((int *)arg);
    while (1)
    {
        pthread_mutex_lock(&config_mutex);
        int value = *active_config;
        pthread_mutex_unlock(&config_mutex);
        printf("Reader %d read config value: %d\n", id, value);
        sleep(1);
    }
    return NULL;
}
void *updater(void *arg)
{
    while (1)
    {
        sleep(3); // Simulate periodic update
        pthread_mutex_lock(&config_mutex);
        // Allocate new config first
        int *new_config = malloc(sizeof(int));
        *new_config = rand() % 100;
        // Save old config
        int *old_config = active_config;
        // Atomic swap
        active_config = new_config;
        free(old_config);
        pthread_mutex_unlock(&config_mutex);
        printf("New config: %d\n", *new_config);
    }
    return NULL;
}
int main()
{
    srand(time(NULL));
    active_config = malloc(sizeof(int));
    *active_config = 10;
    pthread_t r1, r2, r3, up;
    int id1 = 1, id2 = 2, id3 = 3;
    pthread_create(&r1, NULL, reader, &id1);
    pthread_create(&r2, NULL, reader, &id2);
    pthread_create(&r3, NULL, reader, &id3);
    pthread_create(&up, NULL, updater, NULL);
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(up, NULL);
    return 0;
}
