#include "Logging.h"

//#include "CurrentThread.h"
//#include "Timestamp.h"
//#include "TimeZone.h"

#include <errno.h>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cassert>

// tls
__thread char t_errnobuf[512];
__thread char t_time[64];
__thread time_t t_lastSecond;

// 可重定向
const char* strerror_tl(int savedErrno) {
    return strerror_r(savedErrno, t_errnobuf, sizeof t_errnobuf);
}

Logger::LogLevel initLogLevel() {
    if (::getenv("MUDUO_LOG_TRACE"))
        return Logger::TRACE;
    else if (::getenv("MUDUO_LOG_DEBUG"))
        return Logger::DEBUG;
    else
        return Logger::INFO;
}

Logger::LogLevel g_logLevel = initLogLevel();

const char* LogLevelName[Logger::NUM_LOG_LEVELS] = {
    "TRACE ",
    "DEBUG ",
    "INFO  ",
    "WARN  ",
    "ERROR ",
    "FATAL ",
};

struct T
{
    T(const char *str, unsigned len) : str_(str), len_(len) {
        assert(strlen(str) == len_);
    }
    const char *str_;
    const unsigned len_;
};

//inline LogStream& operator<<(LogStream &s, T v) {
    //s.append(v.str_, v.len_);
    //return s;
//}

//inline LogStream& operator<<(LogStream &s, const Logger::SourceFile &v) {
    //s.append(v.str_, v.size_);
    //return s;
//}

void defaultOutput(const char *msg, int len) {
    size_t n = fwrite(msg, 1, len, stdout);
    (void) n;
}

void defaultFlush() {
    fflush(stdout);
}

//Logger::OutputFunc g_output = defaultOutput;
//Logger::defaultFlush g_flush = defaultFlush;
//TimeZone g_logTimeZone;

// dispit line

// Impl
Logger::Impl::Impl(LogLevel level, int savedErrno, const SourceFile &file, int line)
    : time_(Timestamp::now()), stream_(), level_(level), line_(line), basename_(file) {
    formatTime();
    CurrentThread::tid();
    stream_ << T(CurrentThread::tidString(), CurrentThread::tidStringLength());
    stream_ << T(LogLevelName[level], 6);
    if (savedErrno != 0)
        stream_ << strerror_tl(savedErrno) << " (errno=" << savedErrno << ") ";
}
