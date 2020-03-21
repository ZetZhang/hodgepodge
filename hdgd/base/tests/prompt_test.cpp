#include <iostream>
#include <unistd.h>
#include "hdgd/base/prompt.h"

int main(int argc, char *argv[])
{
    int ch;
    // Use 'if' instead of 'while'
    if ((ch = ::getopt(argc, argv, "u:m:f:e:E:n:")) != -1) {
        switch (ch) {
            case 'u':
#ifdef _TUSAGE
                errno = 1;
                hdgd::Prompt::usagePrompt("usage %s\n%s\n", "testing...", ::optarg);
#endif
                break;
            case 'm':
#ifdef _TMSG
                errno = 2;
                hdgd::Prompt::msgPrompt("msg %s\n%s\n", "testing...", ::optarg);
#endif
                break;
            case 'f':
#ifdef _TFATAL
                errno = 3;
                hdgd::Prompt::fatalPrompt("fatal %s\n%s\n", "testing...", ::optarg);
#endif
                break;
            case 'e':
#ifdef _TEXIT3
                errno = 4;
                hdgd::Prompt::exitPrompt("exit %s\n%s\n", "testing...", ::optarg);
#endif
                break;
            case 'E':
#ifdef _TEXIT1
                errno = 5;
                hdgd::Prompt::_ExitPrompt("_Exit %s\n%s\n", "testing...", ::optarg);
#endif
                break;
            case 'n':
#ifdef _TEXIT2
                errno = 6;
                hdgd::Prompt::exitPromptEN(atoi(::optarg), "exitEN %s\n%s\n", "testing...", argv[::optind]);
#endif
                break;
            case '?':
                hdgd::Prompt::usagePrompt("%s\n", "./prompt_test [-umfeE] [-n [errno]] descriptor");
                break;
        }
    } else {
        hdgd::Prompt::usagePrompt("%s\n", "./prompt_test [-umfeE] [-n [errno]] descriptor");
    }

    return 0;
}
