#include <iostream>
#include "mutexlock.h"
#include "condition.h"
#include "singleton.h"

void someFunctionMayCallExit() {
    exit(EXIT_SUCCESS);
}

class GlobalObject /* : public NonCopy */
{
public:
    void doit() {
        hdgd::MutexLockGuard lock(_mutex);
        someFunctionMayCallExit();
    }

    ~GlobalObject() {
        printf("GlobalObject:~GlobalObject\n");
        hdgd::MutexLockGuard lock(_mutex); // death lock
        printf("GlobalObject:~GlobalObject cleanning\n");
    }

private:
    hdgd::MutexLock _mutex;
};

GlobalObject g_obj;

int main(int argc, const char *argv[])
{
    g_obj.doit();
    return 0;
}
