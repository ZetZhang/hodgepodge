#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include <pthread.h>
#include <unistd.h>
#include <assert.h>
//#include "../logging/noncopy.h"

namespace hdgd
{

// CurrentThread
class CurrentThread /* : public NonCopy */
{
public:
    static pid_t tid() { return gettid(); }
    static const char* tidString() { return ""; }
};

// MutexLock
class MutexLock
{
public:
    MutexLock() : _holder(0) {
        pthread_mutex_init(&_mutex, nullptr);
    }
    ~MutexLock() {
        assert(_holder == 0);
        pthread_mutex_destroy(&_mutex);
    }

    bool isLockedByThisThread() {
        return _holder == CurrentThread::tid();
    }

    void assertLocked() {
        assert(isLockedByThisThread());
    }

    void lock() {
        pthread_mutex_lock(&_mutex);
        _holder = CurrentThread::tid();
    }

    void unlock() {
        _holder = 0;
        pthread_mutex_unlock(&_mutex);
    }

    pthread_mutex_t* getPthreadMutex() {
        return &_mutex;
    }

private:
    /* NonCopy
     * MutexLock(const MutexLock &) = delete;
     * const MutexLock& operator=(const MutexLock &) = delete;
     */

    pthread_mutex_t _mutex;
    pid_t _holder;
};

// MutexLockGuard
class MutexLockGuard /* : public NonCopy */
{
public:
    explicit MutexLockGuard(MutexLock &mutex) : _mutex(mutex) {
        _mutex.lock();
    }
    ~MutexLockGuard() {
        _mutex.unlock();
    }

private:
    /* NonCopy
     * MutexLockGuard(const MutexLockGuard &) = delete;
     * const MutexLockGuard& operator=(const MutexLockGuard &);
     */

    MutexLock &_mutex;
};

#define MutexLockGuard(x) static_assert(false, "missing mutex guard var name")

}

#endif
