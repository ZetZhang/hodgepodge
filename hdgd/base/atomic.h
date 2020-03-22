#ifndef __HDGD_ATOMIC_H__
#define __HDGD_ATOMIC_H__

#include "hdgd/base/noncopyable.h"
#include <cstdint>

#if 1
#include <atomic>
#endif

namespace hdgd
{

// C++11 CAS

template<typename T>
class AtomicIntegerCPP11 : NonCopyable {
public:
    AtomicIntegerCPP11() : _value(0) {  }

    T get() {
        return _value.load();
    }

    T getAndAdd(T x) {
        return _value.compare_ex
    }

private:
    std::atomic<T> _value;
};

// Gcc CAS
template<typename T>
class AtomicIntegerGCC : NonCopyable {
public:
    AtomicIntegerGCC() : _value(0) {  }

    T get() {
        return __sync_val_compare_and_swap(&_value, 0, 0);
    }

    T getAndAdd(T x) {
        return _sync_fetch_and_add(&_value, x);
    }

    T addAndGet(T x) {
        return getAndAdd(x) + x;
    }

    T incrementAndGet() {
        return addAndGet(1);
    }

    T decrementAndGet() {
        return addAndGet(-1);
    }

    void add(T x) {
        getAndAdd(x);
    }

    void increment() {
        incrementAndGet();
    }

    void decrement() {
        decrementAndGet();
    }

    T getAndSet(T nVal) {
        return __sync_lock_test_and_set(&_value, nVal);
    }

private:
    volatile T _value;
};
// in gcc >= 4.7 ?
// __atomic_load_n(&_value, __ATOMIC_SEQ_CST);
// __atomic_fetch_add(&_value, x, __ATOMIC_SEQ_CST);
// __atomic_exchange_n(&value, nVal, __ATOMIC_SEQ_CST);

typedef AtomicIntegerGCC<int32_t> AtomicInt32;
typedef AtomicIntegerGCC<int64_t> AtomicInt64;

} // namespace hdgd

#endif
