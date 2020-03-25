#include "hdgd/base/timestamp.h"

#include "hdgd/base/prompt.h"

#include <ctime>
#include <cassert>
#include <cinttypes>

namespace hdgd
{

} // namespace hdgd

using namespace hdgd;

Timestamp::Timestamp(int64_t nanoSecondsSinceEpoch) : _nanoSecondsSinceEpoch(nanoSecondsSinceEpoch) {  }

int64_t Timestamp::getNanoSecondsSinceEpoch() const {
    return _nanoSecondsSinceEpoch;
}

suseconds_t Timestamp::getMicroSecondsSinceEpoch() const {
    return _nanoSecondsSinceEpoch / 1000;
}

time_t Timestamp::getSecondsSinceEpoch() const {
    return static_cast<time_t>(_nanoSecondsSinceEpoch / 1000 / 1000);
}

Timestamp Timestamp::now() {
    // XXX: something errno handle
    struct timespec request;
    if (clock_gettime(CLOCK_REALTIME, &request) == -1)
        Prompt::ExitPrompt("clock_gettime error");
    int64_t seconds = request.tv_sec;
    return Timestamp(seconds * 1000000000 + request.tv_nsec);
}

std::string Timestamp::toString() const {
    char buf[32] = {0};
    int64_t seconds = _nanoSecondsSinceEpoch / 1000000000;
    int32_t milliSeconds = static_cast<int32_t>(_nanoSecondsSinceEpoch % 1000000000 / 1000000);
    int32_t microSeconds = static_cast<int32_t>(_nanoSecondsSinceEpoch % 1000000 / 1000);
    int32_t nanoSeconds = static_cast<int32_t>(_nanoSecondsSinceEpoch % 1000);
    snprintf(buf, sizeof buf, "%" PRIi64 ".%" PRIi32 ".%3" PRIi32 ".%3" PRIi32, seconds, milliSeconds, microSeconds, nanoSeconds);
    return buf;
}

std::string Timestamp::toFormattedString(/* const char *fmt */) {
    // %a %b %d %Y %H:%M:%S %p %Z
    //  Fri 06  Mar 2020 11:21:56 PM CST
    // if ((s = strftime(buf, 34, (fmt) ? fmt : "%a %b %d %Y %H:%M:%S %p %Z"), tm) == 0)
        //Prompt::ExitPrompt("formattedString error");
    //std::cout << daylight << ":" << timezone << ":" << *tzname << ":" << *(tzname + 1) << std::endl;
    // XXX
    char buf[64] = {0};
    time_t seconds = static_cast<time_t>(_nanoSecondsSinceEpoch / 1000000000);
    struct tm tm_time;
    int8_t payLen = 8;
    if (localtime_r(&seconds, &tm_time) == nullptr)
        Prompt::ExitPrompt("gmtime_r error");
    int32_t milliSeconds = static_cast<int32_t>(_nanoSecondsSinceEpoch % 1000000000 / 1000000);
    int32_t microSeconds = static_cast<int32_t>(_nanoSecondsSinceEpoch % 1000000 / 1000);
    int32_t nanoSeconds = static_cast<int32_t>(_nanoSecondsSinceEpoch % 1000);
    if (/* getenv("TZ") != nullptr && */*tzname)
        payLen = sizeof(*tzname);
    snprintf(buf, 33 + payLen, "%04d/%02d/%02d %02d:%02d:%02d.%03" PRIi32 ".%03" PRIi32 ".%03" PRIi32 " %.*s",
                                tm_time.tm_year + 1900,
                                tm_time.tm_mday,
                                tm_time.tm_mday,
                                tm_time.tm_hour,
                                tm_time.tm_min,
                                tm_time.tm_sec,
                                milliSeconds,
                                microSeconds,
                                nanoSeconds,
                                payLen,
                                *tzname);
    return buf;
}

bool Timestamp::operator==(const self &x) const {
    return _nanoSecondsSinceEpoch == x.getNanoSecondsSinceEpoch();
}

bool Timestamp::operator!=(const self &x) const {
    return !(*this == x);
}

bool Timestamp::operator<(const self &x) const {
    return _nanoSecondsSinceEpoch < x.getNanoSecondsSinceEpoch();
}

bool Timestamp::operator<=(const self &x) const {
    return !(*this > x);
}

bool Timestamp::operator>(const self &x) const {
    return _nanoSecondsSinceEpoch > x.getNanoSecondsSinceEpoch();
}

bool Timestamp::operator>=(const self &x) const {
    return !(*this < x);
}
