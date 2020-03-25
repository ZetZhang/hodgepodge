#include <iostream>
#include <cassert>

#include "hdgd/base/atomic.h"

using namespace hdgd;

void checkForAtomicInt32() {
    AtomicInt32 aT32;
    assert(aT32.get() == 0);
    assert(aT32.get_and_set(2) == 0);
    assert(aT32.get_and_increment() == 2);
    assert(aT32.get_and_decrement() == 3);
    aT32.increment();
    assert(aT32.increment_and_get() == 4);
    aT32.decrement();
    assert(aT32.decrement_and_get() == 2);
    assert(aT32.is_lock_free() == true);
    assert(aT32.is_always_lock_free() == true);
    assert(aT32.get_and_add(-2) == 2);
    assert(aT32.add_and_get(2) == 2);
}

void checkForAtomicInt64() {
    AtomicInt64 aT64;
    assert(aT64.get() == 0);
    assert(aT64.get_and_set(2) == 0);
    assert(aT64.get_and_increment() == 2);
    assert(aT64.get_and_decrement() == 3);
    aT64.increment();
    assert(aT64.increment_and_get() == 4);
    aT64.decrement();
    assert(aT64.decrement_and_get() == 2);
    assert(aT64.is_lock_free() == true);
    assert(aT64.is_always_lock_free() == true);
    assert(aT64.get_and_add(-2) == 2);
    assert(aT64.add_and_get(2) == 2);
}

int main(int argc, const char *argv[])
{
    checkForAtomicInt32();
    checkForAtomicInt64();
    return 0;
}
