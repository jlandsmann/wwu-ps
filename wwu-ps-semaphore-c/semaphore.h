//
// Created by Josha Landsmann on 21.06.23.
//

#ifndef WWU_PS_SEMAPHORE_C_SEMAPHORE_H
#define WWU_PS_SEMAPHORE_C_SEMAPHORE_H

#include <pthread.h>

typedef struct semaphore {
    int sem;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} sema_t;

int sema_init(sema_t* sema);

void sema_p(sema_t* sema);

void sema_v(sema_t* sema);

void sema_destroy(sema_t* sema);



#endif //WWU_PS_SEMAPHORE_C_SEMAPHORE_H
