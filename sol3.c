#include "semaphore.h"
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

static int readers = 0;
static int writers = 0;

static semaphore_t mutex;
static semaphore_t resource;

static void *reader(void *arg) {
    struct timespec start_time, end_time;
    double *elapsed_time = (double*) arg;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < 1000; i++) {
        semaphore_wait(&mutex);
        if (writers > 0 || readers == 0) {
            semaphore_signal(&mutex);
            semaphore_wait(&resource);
            semaphore_wait(&mutex);
        }
        readers++;
        semaphore_signal(&mutex);

        // Simulate reading

        semaphore_wait(&mutex);
        readers--;
        if (readers == 0)
            semaphore_signal(&resource);
        semaphore_signal(&mutex);
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
        semaphore_wait(&mutex);
        writers++;
        semaphore_signal(&mutex);
        semaphore_wait(&resource);

        // Simulate writing

        semaphore_wait(&mutex);
        writers--;
        semaphore_signal(&mutex);
        semaphore_signal(&resource);

    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    *elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                    (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
}

void solution3_run(int num_readers, int num_writers, double **reader_time_by_id, double **writer_time_by_id) {

    semaphore_init(&mutex, 1);
    semaphore_init(&resource, 1);

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

    semaphore_destroy(&mutex);
    semaphore_destroy(&resource);
}