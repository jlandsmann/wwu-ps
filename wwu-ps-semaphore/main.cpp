#include <chrono>
#include <iostream>
#include <thread>
#include "semaphore.h"

#define THREAD_COUNT 10

std::thread* threads[THREAD_COUNT];
Semaphore* sema = new Semaphore();

void* doSomeThing(int id)
{
    sema->p();
    printf("Job %d started\n", id);

    for(int i=0; i < 5; ++i) {
        printf("Job %d is doing something\n", id);
        std::this_thread::sleep_for(std::chrono::milliseconds (500));
    };

    printf("Job %d finished\n", id);
    sema->v();

    return nullptr;
}

int main() {
    int i = 0;
    while(i < THREAD_COUNT)
    {
        threads[i] = new std::thread(doSomeThing, i);
        i++;
    }

    i = 0;
    while(i < THREAD_COUNT)
    {
        threads[i]->join();
        i++;
    }
    return 0;
}
