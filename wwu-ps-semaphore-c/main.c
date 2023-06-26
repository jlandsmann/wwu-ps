#include <stdio.h>
#include <string.h>
#include <libc.h>
#include "semaphore.h"

#define THREAD_COUNT 10

pthread_t tid[THREAD_COUNT];
sema_t sema;

void* doSomeThing(void* arg)
{
    sema_p(&sema);
    int id = *(int*)(arg);
    printf("Job %d started\n", id);

    for(int i=0; i < 3; ++i) {
        printf("Job %d is doing something\n", id);
        sleep(1);
    };

    printf("Job %d finished\n\n", id);

    sema_v(&sema);

    return NULL;
}

int main() {
    if (sema_init(&sema) != 0)
    {
        printf("\n sema init failed\n");
        return 1;
    }

    int err = 0;
    int i = 0;
    while(i < THREAD_COUNT)
    {
        int* id = malloc(sizeof(int));
        *id = i;
        err = pthread_create(&(tid[i]), NULL, doSomeThing, id);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }

    i = 0;
    while(i < THREAD_COUNT)
    {
        pthread_join(tid[i], NULL);
        i++;
    }

    sema_destroy(&sema);
    return 0;
}
