#include <chrono>
#include <iostream>
#include <thread>
#include "semaphore.h"

#define THREAD_COUNT 100

std::thread* threads[THREAD_COUNT];
semaphore* sema = new semaphore();;

void* doSomeThing(int id)
{
    sema->p();
    std::cout << "Job " << id << " started " << std::endl;

    for(int i=0; i < 5; ++i) {
        std::cout << "Job " << id << " is doing something" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds (100));
    };

    std::cout << "Job " << id << " finished " << std::endl;
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
