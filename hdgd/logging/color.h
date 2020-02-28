#ifndef __COLOR_H__
#define __COLOR_H__

#include "noncopy.h"
#include <iostream>
#include <utility>
#include <string>
#include <cstring>
#include <memory>

namespace hdgd
{

struct Color
{
    enum class FontColor {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        PURPLE,
        SKYBLUE,
        WHITE,
        NUM_FONT_COLOR,
    };
    enum class BackgroundColor {
        BLACK_BACK,
        RED_BACK,
        GREEN_BACK,
        YELLOW_BACK,
        BLUE_BACK,
        PURPLE_BACK,
        SKYBLUE_BACK,
        WHITE_BACK,
        NONE,
        NUM_BACKGROUND_COLOR,
    };
    static const std::pair<const char*, const char*> portion(Color::FontColor front, Color::BackgroundColor back);
};

template<size_t SIZE>
class ColorStr : public NonCopy
{
public:
    ColorStr() : _data() {}
    ColorStr(const char *buf) : _data(buf) {}
    ColorStr(const std::string &buf) : _data(buf) {}

    const std::string operator()(const char *buf, Color::FontColor front, Color::BackgroundColor back) {
        const std::pair<const std::string, const std::string> add = Color::portion(front, back);
        return std::string(add.first + buf + add.second);
    }

    std::string fromString() {
        return std::string(_data, SIZE);
    }

    const std::string toString(Color::FontColor front, Color::BackgroundColor back) {
        if (!strlen(_data)) {
            /* error */
            return "";
        } else {
            return operator()(_data, front, back);
        }
    }
private:
    char _data[SIZE];
};

} // namespace hdgd

#endif
