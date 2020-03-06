#ifndef __TIMESTAMP_H__
#define __TIMESTAMP_H__

//#define _POSIX_C_SOURCE 199309
#include "rigidstructure/copyable.h"
#include "rigidstructure/comparable.h"
#include "rigidstructure/debug.h"

#include <string>

#include <sys/types.h>

namespace hdgd
{

class Timestamp : public Copyable, public Comparable<Timestamp>, public Debug {
public:
    typedef Timestamp self;

    Timestamp();
    Timestamp(int64_t nanoSecondsSinceEpoch);

    int64_t nanoSecondsSinceEpoch() const;
    suseconds_t microSecondsSinceEpoch() const;
    time_t secondsSinceEpoch() const;

    static Timestamp now();
    //Timestamp fromString() {  }
    std::string toString() const;
    std::string toFormattedString(/* const char *fmt */);

    bool operator==(const self &x) const;
    bool operator!=(const self &x) const;
    bool operator<(const self &x) const;
    bool operator<=(const self &x) const;
    bool operator>(const self &x) const;
    bool operator>=(const self &x) const;

    inline friend double TimeDifference(Timestamp left, Timestamp right);
    // seconds time
    inline friend Timestamp IncrementTime(Timestamp tstamp, double atime);


private:
    int64_t _nanoSecondsSinceEpoch;
};

double TimeDifference(Timestamp left, Timestamp right) {
    return static_cast<double>(left._nanoSecondsSinceEpoch - right._nanoSecondsSinceEpoch) / 1000000000;
}
// seconds time
Timestamp IncrementTime(Timestamp tstamp, double atime) {
    return Timestamp(tstamp._nanoSecondsSinceEpoch + atime * 1000000000);
}

}

#endif
