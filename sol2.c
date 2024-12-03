#include "semaphore.h"
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

static int readers = 0;
static int writers = 0;
static semaphore_t resource;
static semaphore_t readtry;
static semaphore_t rentry;
static semaphore_t rmutex;
static semaphore_t wmutex;

static void *reader(void *arg) {
    struct timespec start_time, end_time;
    double *elapsed_time = (double*) arg;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < 1000; i++) {
        semaphore_wait(&rentry);
        semaphore_wait(&readtry);
        semaphore_wait(&rmutex);
        readers++;
        if (readers == 1)
            semaphore_wait(&resource);
        semaphore_signal(&rmutex);
        semaphore_signal(&readtry);
        semaphore_signal(&rentry);

        // Simulate reading

        semaphore_wait(&rmutex);
        readers--;
        if (readers == 0)
            semaphore_signal(&resource);
        semaphore_signal(&rmutex);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    *elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                    (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
}

static void *writer(void *arg) {
    struct timespec start_time, end_time;
    double *elapsed_time = (double*) arg;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < 1000; i++) {
        semaphore_wait(&wmutex);
        writers++;
        if (writers == 1)
            semaphore_wait(&readtry);
        semaphore_signal(&wmutex);

        semaphore_wait(&resource);

        // Simulate writing

        semaphore_signal(&resource);

        semaphore_wait(&wmutex);
        writers--;
        if (writers == 0)
            semaphore_signal(&readtry);
        semaphore_signal(&wmutex);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    *elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                    (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
}

void solution2_run(int num_readers, int num_writers, double **reader_time_by_id, double **writer_time_by_id) {

    semaphore_init(&resource, 1);
    semaphore_init(&readtry, 1);
    semaphore_init(&rentry, 1);
    semaphore_init(&rmutex, 1);
    semaphore_init(&wmutex, 1);

    pthread_t threads [num_readers + num_writers];

    for (int i = 0; i < num_readers; i++) {
        pthread_create(&threads[i], NULL, reader, &(reader_time_by_id[i]));
    }

    for (int i = 0; i < num_writers; i++) {
        pthread_create(&threads[i + num_readers], NULL, writer, &(writer_time_by_id[i]));
    }

    for (int i = 0; i < num_readers + num_writers; i++) {
        pthread_join(threads[i], NULL);
    }

    semaphore_destroy(&resource);
    semaphore_destroy(&readtry);
    semaphore_destroy(&rentry);
    semaphore_destroy(&rmutex);
    semaphore_destroy(&wmutex);
}