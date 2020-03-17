#include "hdgd/base/color.h"

namespace hdgd
{

static const char* ForeColorCode[static_cast<unsigned char>(Color::ForeColor::NUM_FORE_COLOR)] = {
    "30m", "31m", "32m", "33m", "34m", "35m", "36m", "37m",
};

static const char* BackgroundColorCode[static_cast<unsigned char>(Color::BackgroundColor::NUM_BACKGROUND_COLOR)] = {
    "40;", "41;", "42;", "43;", "44;", "45;", "46;", "47;", ""
};

} // namespace hdgd


using namespace hdgd;

// FIXME:需要区分有无底色，无底色5，底色8，结尾4。则每个\r\n需要塞9+1个字节或12+1个字节
// Need a string piece
// FIXME: out of data
//const std::pair<const char*, const char*> Color::portion(Color::ForeColor front, Color::BackgroundColor back) {
    //// if back == "" { hasn't bg } else { has bg }
    //using std::string;
    //const std::string head("\033["
            //+ string(BackgroundColorCode[static_cast<unsigned int>(back)])
            //+ string(ForeColorCode[static_cast<unsigned int>(front)]));
    //const char *tail = "\033[0m\r\n";
    //return std::make_pair(head.c_str(), tail);
//}

const std::pair<const char*, const char*> Color::portion(Color::ForeColor front, Color::BackgroundColor back) {
    std::string head("\033[");
    head.append(BackgroundColorCode[static_cast<unsigned int>(back)]);
    head.append(ForeColorCode[static_cast<unsigned int>(front)]);
    return std::make_pair(head.c_str(), "\033[0m");
}
