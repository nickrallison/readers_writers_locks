#include "semaphore.h"
#include <stdlib.h>

void semaphore_init(semaphore_t *s, int value) {
    s->value = value;
    pthread_mutex_init(&(s->mutex), NULL);
    s->queue_head = s->queue_tail = NULL;
}

void semaphore_wait(semaphore_t *s) {
    pthread_mutex_lock(&(s->mutex));
    s->value--;
    if (s->value < 0) {
        waiting_thread_t *wt = (waiting_thread_t *)malloc(sizeof(waiting_thread_t));
        pthread_cond_init(&(wt->cond), NULL);
        wt->signaled = 0;
        wt->next = NULL;

        if (s->queue_tail == NULL) {
            s->queue_head = s->queue_tail = wt;
        } else {
            s->queue_tail->next = wt;
            s->queue_tail = wt;
        }

        while (wt->signaled == 0) {
            pthread_cond_wait(&(wt->cond), &(s->mutex));
        }
        pthread_cond_destroy(&(wt->cond));
        free(wt);
    }
    pthread_mutex_unlock(&(s->mutex));
}

void semaphore_signal(semaphore_t *s) {
    pthread_mutex_lock(&(s->mutex));
    s->value++;
    if (s->value <= 0) {
        waiting_thread_t *wt = s->queue_head;
        if (wt != NULL) {
            s->queue_head = wt->next;
            if (s->queue_head == NULL)
                s->queue_tail = NULL;
            wt->signaled = 1;
            pthread_cond_signal(&(wt->cond));
        }
    }
    pthread_mutex_unlock(&(s->mutex));
}

void semaphore_destroy(semaphore_t *s) {
    pthread_mutex_destroy(&(s->mutex));

    waiting_thread_t *wt = s->queue_head;
    while (wt != NULL) {
        waiting_thread_t *next = wt->next;
        pthread_cond_destroy(&(wt->cond));
        free(wt);
        wt = next;
    }
    s->queue_head = s->queue_tail = NULL;
}