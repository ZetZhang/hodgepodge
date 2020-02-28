#include "prompt.h"
#include "ename.c.inc"
#include "color.h"

#include <cstdarg>
#include <cerrno>
#include <string>

namespace hdgd
{

static void __terminate(bool useExit) {
    char *s = getenv("_DUMPCORE");
    if (s != nullptr && *s != '\0')
        abort();
    else if (useExit)
        exit(EXIT_FAILURE);
    else
        _Exit(EXIT_FAILURE);
}

static void __outputPrompt(bool useErr, int errn, const std::string format, va_list ap) {
    char buf[EO_BUF_SIZE], userMsg[EO_BUF_SIZE], errText[EO_BUF_SIZE];
    vsnprintf(userMsg, EO_BUF_SIZE, format.c_str(), ap);
    if (useErr)
        snprintf(errText, EO_BUF_SIZE, " [%s %s]",
                (errn > 0 && errn <= MAX_ENAME) ? ename[errn] : "?UNKNOWN?", strerror(errn));
    else
        snprintf(errText, EO_BUF_SIZE, ":");
    snprintf(buf, EO_BUF_SIZE, "ERROR%s %s", errText, userMsg);
    fflush(stdout);
    ColorStr<0> colorStr;
    fputs(buf, stderr);
    fflush(stderr);
}


} // namespace hdgd


using namespace hdgd;

void Prompt::msgPrompt(const char *format, ...) {
    va_list argList;
    int savedErrno = errno;
    va_start(argList, format);
    ColorStr<0> colorStr;
    __outputPrompt(true, errno,
            colorStr(format, Color::FontColor::GREEN, Color::BackgroundColor::NONE), argList);
    va_end(argList);
    errno = savedErrno;
}

void Prompt::usagePrompt(const char *format, ...) {
    va_list argList;
    fflush(stdout);
    va_start(argList, format);
    ColorStr<0> colorStr;
    vfprintf(stderr, colorStr(std::string("usage error: " + std::string(format)).c_str(),
                Color::FontColor::SKYBLUE, Color::BackgroundColor::NONE).c_str(),
                argList);
    va_end(argList);
    fflush(stderr);
    exit(EXIT_FAILURE);
}

void Prompt::fatalPrompt(const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    ColorStr<0> colorStr;
    __outputPrompt(false, 0,
            colorStr(format, Color::FontColor::WHITE, Color::BackgroundColor::RED_BACK), argList);
    va_end(argList);
    __terminate(true);
}

void Prompt::exitPrompt(const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    ColorStr<0> colorStr;
    __outputPrompt(false, errno,
            colorStr(format, Color::FontColor::RED, Color::BackgroundColor::NONE), argList);
    va_end(argList);
    __terminate(true);
}

void Prompt::exitPromptEN(int errn, const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    ColorStr<0> colorStr;
    __outputPrompt(true, errn,
            colorStr(format, Color::FontColor::RED, Color::BackgroundColor::NONE), argList);
    va_end(argList);
    __terminate(true);
}

void Prompt::_ExitPrompt(const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    ColorStr<0> colorStr;
    __outputPrompt(true, errno,
            colorStr(format, Color::FontColor::RED, Color::BackgroundColor::WHITE_BACK), argList);
    //__outputPrompt(true, errno, format, argList);
    va_end(argList);
    __terminate(false);
}