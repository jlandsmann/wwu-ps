//
// Created by Josha Landsmann on 21.06.23.
//
#include <stdlib.h>
#include "semaphore.h"

int sema_init(sema_t* sema) {
    sema->sem = 1;
    if (pthread_mutex_init(&sema->mutex, NULL) != 0) {
        return 1;
    } else if (pthread_cond_init(&sema->cond, NULL) != 0) {
        return 1;
    }
    return 0;
}

void sema_p(sema_t* sema) {
    pthread_mutex_lock(&sema->mutex);
    while (sema->sem < 1) {
        pthread_cond_wait(&sema->cond, &sema->mutex);
    }
    sema->sem = 0;
    pthread_mutex_unlock(&sema->mutex);

}

void sema_v(sema_t* sema) {
    pthread_mutex_lock(&sema->mutex);
    sema->sem = 1;
    pthread_cond_signal(&sema->cond);
    pthread_mutex_unlock(&sema->mutex);

}

void sema_destroy(sema_t* sema) {
    sema->sem = -1;
    pthread_mutex_destroy(&sema->mutex);
    pthread_cond_destroy(&sema->cond);
}

