//
// Created by Josha Landsmann on 21.06.23.
//

#include "semaphore.h"

Semaphore::Semaphore(int concurrency) : counter(concurrency) {}

void Semaphore::p() {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->cond.wait(lock, [&]{ return counter != 0;});
    this->counter--;
}

void Semaphore::v() {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->counter++;
    this->cond.notify_one();
}
