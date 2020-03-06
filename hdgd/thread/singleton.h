#ifndef __SINGLETON_H__
#define __SINGLETON_H__

//#include "noncopy.h"
#include <pthread.h>
#include <stdlib.h>

namespace hdgd
{

// ??
template<typename T>
struct __hasNoDestroy
{
  template <typename C> static char test(decltype(&C::no_destroy));
  template <typename C> static int32_t test(...);
  const static bool value = sizeof(test<T>(0)) == 1;
};


template<typename T>
class Singleton /* : public NonCopy */
{
public:
    static T& instance() {
        pthread_once(&_ponce, &Singleton::init);
        return *_value;
    }

private:
    /* NonCopy
     * Singleton(const Singleton &) = delete;
     * const Singleton& operator=(const Singleton &) = delete;
     */

    Singleton() = delete;
    ~Singleton() = delete;

    static void init() {
        _value = new T();
        if (__hasNoDestroy<T>::value)
            atexit(destroy);
    }

    static void destroy() {
        using T_must_be_complete_type = char[sizeof(T) == 0 ? -1 : 1];
        T_must_be_complete_type dummy; (void) dummy;
        delete _value;
        _value = nullptr;
    }

    static pthread_once_t _ponce;
    static T *_value;
};

template<typename T>
pthread_once_t Singleton<T>::_ponce = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::_value = nullptr;

}

#endif
