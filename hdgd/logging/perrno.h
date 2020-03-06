#ifndef __PERRNO_H__
#define __PERRNO_H__

#include "rigidstructure/noncopyable.h"
#include <pthread.h>
#include <memory.h>

//#ifndef __ASSEMBLER__
    // Undefine __ASSEMBLER__
//#else
    // define __ASSEMBLER__
//#endif
//#ifndef __LIBC
    //Undefine __LIBC
//#else
    //define __LIBC
//#endif
//#ifndef _LIBC_REENTRANT
    //Undefine _LIBC_REENTRANT
//#else
    //define _LIBC_REENTRANT
//#endif

extern int *__errno_location(void) __THROW __attribute__((__const__));

namespace hdgd
{

//__thread int _errnoTID;
static pthread_key_t _enoKey;
static pthread_once_t _enoKeyOnce = PTHREAD_ONCE_INIT;

int* _pErrno() {
    int *ePtr;
    static auto _make_key = [&_enoKey] { pthread_key_create(&_enoKey, nullptr); };
    pthread_once(&_enoKeyOnce, _make_key);
    if ((ePtr = static_cast<int*>(pthread_getspecific(_enoKey))) == nullptr) {
        //ePtr = static_cast<int*>(malloc(sizeof(int)));
        ePtr = __errno_location();
        pthread_setspecific(_enoKey, ePtr);
    }
    return ePtr;
}

}

#endif
