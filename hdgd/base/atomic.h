#ifndef __HDGD_ATOMIC_H__
#define __HDGD_ATOMIC_H__

//#include "hdgd/base/noncopyable.h"
#include <cstdint>

#if (__cplusplus >= 201103L)
#include <atomic>
#define __cpp11
#endif

namespace hdgd
{

// Gcc CAS
template<typename T>
class AtomicInteger {
public:
    AtomicInteger() : value_(0) {  }
    AtomicInteger(const AtomicInteger &x) : value_(x.get()) {  }
    AtomicInteger& operator=(const AtomicInteger &x) { get_and_set(x.get()); return *this; }

    T get() {
#ifdef __cpp11
        return std::atomic_load_explicit(&value_, std::memory_order_seq_cst);
#else
        return __atomic_load_n(&value_, __ATOMIC_SEQ_CST);
#endif
    }

    T get_and_add(T x) {
#ifdef __cpp11
        return std::atomic_fetch_add_explicit(&value_, x, std::memory_order_release);
#else
        return __atomic_fetch_add(&value_, x, __ATOMIC_RELEASE);
#endif
    }

    T add_and_get(T x) {
#ifdef __cpp11
        return get_and_add(x) + x;
#else
        return __atomic_add_fetch(&value_, x, __ATOMIC_RELEASE);
#endif
    }

    T increment_and_get() { return add_and_get(1); }
    T decrement_and_get() { return add_and_get(-1); }
    T get_and_increment() { return get_and_add(1); }
    T get_and_decrement() { return get_and_add(-1); }

    void add(T x) { add_and_get(x); }
    void increment() { increment_and_get(); }
    void decrement() { decrement_and_get(); }

    T get_and_set(T nVal) {
#ifdef __cpp11
        return std::atomic_exchange_explicit(&value_, nVal, std::memory_order_acquire);
#else
        return __atomic_exchange_n(&value_, nVal, __ATOMIC_ACQUIRE);
#endif
    }

    /// The ‘__atomic’ builtins can be used with any integral scalar or pointer
    /// type that is 1, 2, 4, or 8 bytes in length. 16-byte integral types are
    /// also allowed if ‘__int128’ (see __int128) is supported by the
    /// architecture.
    bool is_lock_free() {
#ifdef __cpp11
        return std::atomic_is_lock_free(&value_);
#else
        return __atomic_is_lock_free(sizeof(T), 0);
#endif
    }

    bool is_always_lock_free() {
#ifdef __cpp11
        return is_lock_free();
#else
        return __atomic_always_lock_free(sizeof(T), 0);
#endif
    }

private:
#ifdef __cpp11
    volatile std::atomic<T> value_;
#else
    volatile T value_;
#endif
};

typedef AtomicInteger<int32_t> AtomicInt32;
typedef AtomicInteger<int64_t> AtomicInt64;
//typedef AtomicInteger<__int128> AtomicInt128;

} // namespace hdgd

#endif
