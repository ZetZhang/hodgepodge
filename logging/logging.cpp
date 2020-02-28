#include "logging.h"

#include <cstdlib>

namespace hdgd
{

const char* LogLevelName[static_cast<unsigned int>(Logger::LogLevel::NUM_LOG_LEVEL)] = {
    "TRACE ",
    "DEBUG ",
    "INFO  ",
    "WARN  ",
    "ERROR ",
    "FATAL ",
};

static Logger::LogLevel initLogLevel() {
    if (getenv("_LOG_TRACE"))
        return Logger::LogLevel::TRACE;
    else if (getenv("_LOG_DEBUG"))
        return Logger::LogLevel::DEBUG;
    else
        return Logger::LogLevel::INFO;
}

extern Logger::LogLevel g_LogLevel = initLogLevel();

} // namespace hdgd


using namespace hdgd;
