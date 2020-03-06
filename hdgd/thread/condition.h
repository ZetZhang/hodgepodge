#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "mutexlock.h"

namespace hdgd
{

class Condition /* : public NonCopy */
{
public:
    explicit Condition(MutexLock &mutex) : _mutex(mutex) {
        pthread_cond_init(&_pcond, nullptr);
    }
    ~Condition() {
        pthread_cond_destroy(&_pcond);
    }

    void wait() {
        pthread_cond_wait(&_pcond, _mutex.getPthreadMutex());
    }

    void notify() {
        pthread_cond_signal(&_pcond);
    }

    void notifyAll() {
        pthread_cond_broadcast(&_pcond);
    }

private:
    /* NonCOpy
     * Condition(const Condition &) = delete;
     * const Condition& operator=(const Condition &) = delete;
     */

    MutexLock _mutex;
    pthread_cond_t _pcond;
};

class CountDownLatch
{
public:
    CountDownLatch(int count) : _mutex(), _condition(_mutex), _count(count) {  }

private:
    mutable MutexLock _mutex;
    Condition _condition;
    int _count;
};

}

#endif
