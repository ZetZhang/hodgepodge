#ifndef __HDGD_TIMESTAMP_H__
#define __HDGD_TIMESTAMP_H__

//#define _POSIX_C_SOURCE 199309
#include "hdgd/base/copyable.h"
#include "hdgd/base/comparable.h"
#include "hdgd/base/debug.h"

#include <string>

#include <sys/types.h>

namespace hdgd
{

class Timestamp : public Copyable/* , public Comparable<Timestamp>, public Debug */ {
public:
    typedef Timestamp self;

    explicit Timestamp(int64_t nanoSecondsSinceEpoch);

    int64_t getNanoSecondsSinceEpoch() const;
    suseconds_t getMicroSecondsSinceEpoch() const;
    time_t getSecondsSinceEpoch() const;

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


private:
    int64_t _nanoSecondsSinceEpoch;
};

// non-member non-friend functions
// XXX
inline double TimeDifference(Timestamp left, Timestamp right) {
    return static_cast<double>(left.getNanoSecondsSinceEpoch() - right.getNanoSecondsSinceEpoch()) / 1000000000;
}
// seconds time
// XXX
inline Timestamp AddTime(Timestamp tstamp, double atime) {
    return Timestamp(tstamp.getNanoSecondsSinceEpoch() + static_cast<int64_t>(atime * 1000000000));
}


}

#endif
