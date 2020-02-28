#ifndef __PROMPT_H__
#define __PROMPT_H__

#include <stdlib.h>

static const size_t EO_BUF_SIZE = 500;

namespace hdgd
{

class Prompt
{
public:
#define NORETURN __attribute__ ((__noreturn__))
    static void msgPrompt(const char *format, ...) NORETURN;
    static void usagePrompt(const char *format, ...) NORETURN;
    static void fatalPrompt(const char *format, ...) NORETURN;
    static void exitPrompt(const char *format, ...) NORETURN;
    static void _ExitPrompt(const char *format, ...) NORETURN;
    static void exitPromptEN(int errn, const char *format, ...) NORETURN;
#undef NORETURN
};

//class outputStream;
// ^
/*
 * hdgd::msg <<
 * msg / cmdLine / usage / fatal / exit
 */
//class msg : public OutputStream;
//class uasge : public OutputStream;
//class fatal : public OutputStream;
//class exit : public OutputStream;
//Pormpt& operator<<(ostream&, ...)


} // namespace hdgd

#endif
