#include "hdgd/base/prompt.h"
#include "hdgd/base/ename.c.inc"
#include "hdgd/base/color.h"

#include <cstdarg>
#include <cerrno>
#include <string>


namespace hdgd
{

namespace detail
{

__thread char __t_errnobuf[512];
const char* strerror_rT(int savedErrno) {
    return strerror_r(savedErrno, __t_errnobuf, sizeof(__t_errnobuf));
}

static void __terminate(bool useExit) {
    char *s = getenv("_DUMPCORE");
    if (s != nullptr && *s != '\0')
        abort();
    else if (useExit)
        exit(EXIT_FAILURE);
    else
        _Exit(EXIT_FAILURE);
}

static void __outputPrompt(bool useErr, int errn, const char *format, color::ForeColor fore, color::BackgroundColor back, va_list ap) {
    int wlen;
    char buf[EO_BUF_SIZE], userMsg[EO_BUF_SIZE], errText[EO_BUF_SIZE];
    // FIXME: About the buffer overflow
    vsnprintf(userMsg, EO_BUF_SIZE, format, ap);
    if (useErr)
        wlen = snprintf(errText, EO_BUF_SIZE, " [%s %s]:",
                (errn > 0 && errn <= MAX_ENAME) ? ename[errn] : "?UNKNOWN?", strerror_rT(errn));
    else
        wlen = snprintf(errText, 2, ":");
    snprintf(buf, EO_BUF_SIZE + wlen, "ERROR%s %s\n", errText, userMsg);
    fflush(stdout);
    ColorStr<EO_BUF_SIZE> colorStr(buf, fore, back);
    fputs(colorStr.toColoredCStr(), stderr);
    fflush(stderr);
}

}

} // namespace hdgd


using namespace hdgd;
using namespace hdgd::detail;

void Prompt::MsgPrompt(const char *format, ...) {
    va_list argList;
    int savedErrno = errno;
    va_start(argList, format);
    __outputPrompt(true, errno, format, color::ForeColor::BLUE, color::BackgroundColor::NONE, argList);
    va_end(argList);
    errno = savedErrno;
}

void Prompt::UsagePrompt(const char *format, ...) {
    va_list argList;
    fflush(stdout);
    va_start(argList, format);
    std::string usageBuf("usage error: ");
    usageBuf.append(format);

    ColorStr<EO_BUF_SIZE> colorStr(usageBuf, color::ForeColor::SKYBLUE, color::BackgroundColor::NONE);
    vfprintf(stderr, colorStr.toColoredCStr(), argList);
    va_end(argList);
    fflush(stderr);
    exit(EXIT_FAILURE);
}

void Prompt::FatalPrompt(const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    __outputPrompt(true, errno, format, color::ForeColor::WHITE, color::BackgroundColor::RED_BACK, argList);
    va_end(argList);
    __terminate(true);
}

void Prompt::ExitPrompt(const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    __outputPrompt(true, errno, format, color::ForeColor::RED, color::BackgroundColor::NONE, argList);
    va_end(argList);
    __terminate(true);
}

void Prompt::ExitPromptEN(int errn, const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    __outputPrompt(true, errno, format, color::ForeColor::WHITE, color::BackgroundColor::BLACK_BACK, argList);
    va_end(argList);
    __terminate(true);
}

void Prompt::_ExitPrompt(const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    __outputPrompt(true, errno, format, color::ForeColor::RED, color::BackgroundColor::WHITE_BACK, argList);
    va_end(argList);
    __terminate(false);
}
