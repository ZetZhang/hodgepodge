#include "color.h"

namespace hdgd
{

static const char* ForeColorCode[static_cast<unsigned int>(Color::ForeColor::NUM_FONT_COLOR)] = {
    "30m", "31m", "32m", "33m", "34m", "35m", "36m", "37m",
};

static const char* BackgroundColorCode[static_cast<unsigned int>(Color::BackgroundColor::NUM_BACKGROUND_COLOR)] = {
    "40;", "41;", "42;", "43;", "44;", "45;", "46;", "47;", ""
};

} // namespace hdgd


using namespace hdgd;

const std::pair<const char*, const char*> Color::portion(Color::ForeColor front, Color::BackgroundColor back) {
    using std::string;
    const std::string head("\033["
            + string(BackgroundColorCode[static_cast<unsigned int>(back)])
            + string(ForeColorCode[static_cast<unsigned int>(front)]));
    const char *tail = "\033[0m";
    return std::make_pair(head.c_str(), tail);
}

