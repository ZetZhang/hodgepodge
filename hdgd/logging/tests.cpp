#include <iostream>
#include "prompt.h"
#include "color.h"
//#include "singleton.h"
#include "perrno.h"
#include "timestamp.h"

#include <signal.h>
#include <unistd.h>
#include <time.h>

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
    //pid_t curr = getpid();
    //kill(curr, 22222);
    //int *_tlsE = hdgd::_pErrno();
    //std::cout << errno << std::endl;

    hdgd::Timestamp s, j, t;
    s = hdgd::Timestamp::now();
    std::cout << s.nanoSecondsSinceEpoch() << std::endl;
    j = hdgd::Timestamp::now();
    std::cout << j.nanoSecondsSinceEpoch() << std::endl;
    t = hdgd::IncrementTime(j, 3.5f);
    std::cout << t.nanoSecondsSinceEpoch() << std::endl;
    std::cout << hdgd::TimeDifference(t, j) << std::endl;
    std::cout << t.toFormattedString() << std::endl;
    std::cout << t.toString() << std::endl;
    return 0;
}
