#include "semaphore.h"
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int readers = 0;
semaphore_t resource;
semaphore_t mutex;

void *reader(void *arg) {
    struct timespec start_time, end_time;
    double *elapsed_time = malloc(sizeof(double));

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < 1000; i++) {
        semaphore_wait(&mutex);
        readers++;
        if (readers == 1)
            semaphore_wait(&resource);
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
    return (void *)elapsed_time;
}

void *writer(void *arg) {
    struct timespec start_time, end_time;
    double *elapsed_time = malloc(sizeof(double));

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < 1000; i++) {
        semaphore_wait(&resource);

        // Simulate writing

        semaphore_signal(&resource);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    *elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                    (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    return (void *)elapsed_time;
}

void solution1_run(int num_readers, int num_writers, double *avg_reader_tat, double *avg_writer_tat) {
    pthread_t reader_threads[num_readers];
    pthread_t writer_threads[num_writers];

    semaphore_init(&resource, 1);
    semaphore_init(&mutex, 1);

    double total_reader_time = 0;
    double total_writer_time = 0;

    for (int i = 0; i < num_readers; i++) {
        pthread_create(&reader_threads[i], NULL, reader, NULL);
    }

    for (int i = 0; i < num_writers; i++) {
        pthread_create(&writer_threads[i], NULL, writer, NULL);
    }

    for (int i = 0; i < num_readers; i++) {
        void *elapsed_time;
        pthread_join(reader_threads[i], &elapsed_time);
        total_reader_time += *((double *)elapsed_time);
        free(elapsed_time);
    }

    for (int i = 0; i < num_writers; i++) {
        void *elapsed_time;
        pthread_join(writer_threads[i], &elapsed_time);
        total_writer_time += *((double *)elapsed_time);
        free(elapsed_time);
    }

    *avg_reader_tat = (num_readers > 0) ? total_reader_time / num_readers : 0;
    *avg_writer_tat = (num_writers > 0) ? total_writer_time / num_writers : 0;

    semaphore_destroy(&resource);
    semaphore_destroy(&mutex);
}
