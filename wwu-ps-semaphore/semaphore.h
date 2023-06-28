//
// Created by Josha Landsmann on 21.06.23.
//

#ifndef WWU_PS_SEMAPHORE_SEMAPHORE_H
#define WWU_PS_SEMAPHORE_SEMAPHORE_H

#include <condition_variable>
#include <mutex>
#include <shared_mutex>

class Semaphore {
private:
    int counter;
    std::condition_variable_any cond;
    std::mutex mutex;

public:
    explicit Semaphore(int concurrency = 1);
    void p();
    void v();
};


#endif //WWU_PS_SEMAPHORE_SEMAPHORE_H
