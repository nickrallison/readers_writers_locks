#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <pthread.h>

typedef struct waiting_thread {
    pthread_cond_t cond;
    int signaled;
    struct waiting_thread *next;
} waiting_thread_t;

typedef struct {
    int value;
    pthread_mutex_t mutex;
    waiting_thread_t *queue_head;
    waiting_thread_t *queue_tail;
} semaphore_t;

void semaphore_init(semaphore_t *s, int value);
void semaphore_wait(semaphore_t *s);
void semaphore_signal(semaphore_t *s);
void semaphore_destroy(semaphore_t *s);

#endif