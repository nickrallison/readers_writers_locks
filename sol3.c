#include "semaphore.h"
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

static int readcount = 0;
static int writecount = 0;
static semaphore_t x;
static semaphore_t y;
static semaphore_t z;
static semaphore_t wsem;
static semaphore_t rsem;

static void *reader(void *arg) {
    struct timespec start_time, end_time;
    double *elapsed_time = malloc(sizeof(double));

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < 1000; i++) {
        semaphore_wait(&z);
        semaphore_wait(&rsem);
        semaphore_wait(&x);
        readcount++;
        if (readcount == 1)
            semaphore_wait(&wsem);
        semaphore_signal(&x);
        semaphore_signal(&rsem);
        semaphore_signal(&z);

        // Simulate reading

        semaphore_wait(&x);
        readcount--;
        if (readcount == 0)
            semaphore_signal(&wsem);
        semaphore_signal(&x);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    *elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                    (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    return (void *)elapsed_time;
}

static void *writer(void *arg) {
    struct timespec start_time, end_time;
    double *elapsed_time = malloc(sizeof(double));

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < 1000; i++) {
        semaphore_wait(&y);
        writecount++;
        if (writecount == 1)
            semaphore_wait(&rsem);
        semaphore_signal(&y);

        semaphore_wait(&wsem);

        // Simulate writing

        semaphore_signal(&wsem);

        semaphore_wait(&y);
        writecount--;
        if (writecount == 0)
            semaphore_signal(&rsem);
        semaphore_signal(&y);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    *elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                    (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    return (void *)elapsed_time;
}

void solution3_run(int num_readers, int num_writers, double *avg_reader_tat, double *avg_writer_tat) {
    pthread_t reader_threads[num_readers];
    pthread_t writer_threads[num_writers];

    semaphore_init(&x, 1);
    semaphore_init(&y, 1);
    semaphore_init(&z, 1);
    semaphore_init(&wsem, 1);
    semaphore_init(&rsem, 1);

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

    semaphore_destroy(&x);
    semaphore_destroy(&y);
    semaphore_destroy(&z);
    semaphore_destroy(&wsem);
    semaphore_destroy(&rsem);
}