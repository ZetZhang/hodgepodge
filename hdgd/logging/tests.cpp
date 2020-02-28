#include <iostream>
#include "prompt.h"
#include "color.h"

int main(int argc, const char *argv[])
{
#ifdef _TEXIT1
    hdgd::Prompt::_ExitPrompt("_Exit %s\n", "testing...");
#endif
#ifdef _TEXIT2
    hdgd::Prompt::exitPromptEN(9, "exitEN %s\n", "testing...");
#endif
#ifdef _TEXIT3
    hdgd::Prompt::exitPrompt("exit %s\n", "testing...");
#endif
#ifdef _TMSG
    hdgd::Prompt::msgPrompt("msg %s\n", "testing...");
#endif
#ifdef _TUSAGE
    hdgd::Prompt::usagePrompt("usage %s\n", "testing...");
#endif
#ifdef _TFATAL
    hdgd::Prompt::fatalPrompt("fatal %s\n", "testing...");
#endif
    return 0;
}
