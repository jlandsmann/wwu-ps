//
// Created by Josha Landsmann on 21.06.23.
//

#include "semaphore.h"

semaphore::semaphore() {
    this->counter = 1;
}

void semaphore::p() {
    std::unique_lock<std::mutex> lock(this->mutex);
    while (this->counter < 1) {
        this->cond.wait(lock);
    }
    this->counter = 0;
}

void semaphore::v() {
    std::unique_lock<std::mutex> lock(this->mutex);
    this->counter = 1;
    this->cond.notify_one();
}

semaphore::~semaphore() {
    this->cond.notify_all();
};
