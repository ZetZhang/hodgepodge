#ifndef __LOGGING_H__
#define __LOGGING_H__

namespace hdgd
{

class Logger {
public:
    enum class LogLevel
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVEL,
    };

    Logger() {}
    ~Logger() {}
};


} // namespace hdgd

#endif
