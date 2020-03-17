#ifndef __HDGD_COLOR_H__
#define __HDGD_COLOR_H__

#include "hdgd/base/noncopyable.h"

#include <cstdio>
#include <string>
#include <cstring>

#ifdef DEBUG
static void pri(const char *buf)
{
    char ch;
    char *i = const_cast<char*>(buf);
    printf("[");
    while ((ch = *i++) != '\0')
        printf("%c,", static_cast<char>(ch));
    printf("]\n");
}
#endif

namespace hdgd
{

struct Color
{
    enum class ForeColor {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        PURPLE,
        SKYBLUE,
        WHITE,
        NUM_FORE_COLOR,
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
    static const std::pair<const char*, const char*> portion(Color::ForeColor front, Color::BackgroundColor back);
};

template<size_t LEFT, size_t RIGHT>
size_t TMP_CMP_LEN() {
    return LEFT > RIGHT ? LEFT : RIGHT;
}

// Normal
template<size_t SIZE>
class ColorStr
{
public:
    ColorStr();
    ColorStr(const char *buf);
    ColorStr(const std::string &buf);
    ~ColorStr() noexcept;

    // FIXME: The move constructor did not pass
    //template<size_t OSIZE>
    //ColorStr<TMP_CMP_LEN<SIZE, OSIZE>()>(ColorStr<OSIZE> &&x) noexcept;

    // FIXME: The move constructor did pass
    template<size_t OSIZE>
    ColorStr<TMP_CMP_LEN<SIZE, OSIZE>()>& operator=(ColorStr<OSIZE> &&x) noexcept;

    // FIXME: should be return the string piece
    const std::string operator()(const char *buf, Color::ForeColor front, Color::BackgroundColor back) {
        //const std::pair<const std::string, const std::string> pieces = Color::portion(front, back);
        const std::pair<const char*, const char*> pieces = Color::portion(front, back);
        // FIXME: Parsing the output problem of newline segments
#ifdef DEBUG
        //std::string tmp(std::string(pieces.first) + buf + std::string(pieces.second));
        //pri(tmp.c_str());
        //std::string tmp(pieces.first + buf + pieces.second);
        //pri(tmp.c_str());
#endif
        return std::string(std::string(pieces.first) + buf + std::string(pieces.second));
        //return std::string(pieces.first + buf + pieces.second);
    }

    std::string fromString() {
        return std::string(_data, SIZE);
    }

    const std::string toString(Color::ForeColor front, Color::BackgroundColor back) {
        if (!strlen(_data)) {
            /* XXX: There is no zero length anymore */
            return nullptr;
        } else {
            return operator()(_data, front, back);
        }
    }
private:
    char _data[SIZE];
    std::string *_convertStr;
};

// Partial
// FIXME: Something wrong
template<>
class ColorStr<0> : NonCopyable
{
public:
    ColorStr() = default;
    //const std::string operator()(const char *buf, Color::ForeColor front, Color::BackgroundColor back) {
        //const std::pair<const std::string, const std::string> add = Color::portion(front, back);
        //return std::string(add.first + buf + add.second);
    //}

    // XXX:只适合单行
    const std::string operator()(const char *buf, Color::ForeColor front, Color::BackgroundColor back) {
        const std::pair<const char*, const char*> pieces = Color::portion(front, back);
#ifdef DEBUG
        //std::string tmp(std::string(pieces.first) + buf + std::string(pieces.second));
        //pri(tmp.c_str());
        //std::string tmp(pieces.first + buf + pieces.second);
        //pri(tmp.c_str());
#endif
        return std::string(std::string(pieces.first) + buf + std::string(pieces.second));
        //return std::string(pieces.first + buf + pieces.second);
    }
private:
    ColorStr(ColorStr &&) noexcept = delete;
    ColorStr& operator=(ColorStr &&) noexcept = delete;
};

template<size_t SIZE>
ColorStr<SIZE>::ColorStr() : _data() { printf("Color fucking.\n"); }

template<size_t SIZE>
ColorStr<SIZE>::ColorStr(const char *buf) : _data(buf) {}

template<size_t SIZE>
ColorStr<SIZE>::ColorStr(const std::string &buf) : _data(buf) {}

template<size_t SIZE>
ColorStr<SIZE>::~ColorStr() {

}

// FIXME: 类型模板参数的固化
//template<size_t SIZE>
//ColorStr<SIZE>::ColorStr(ColorStr &&x)[> : _data(std::move(x._data)) <]{
    //_data =
    //x._data = nullptr;
//}

// FIXME: has a difference exception specifier
//template<size_t SIZE>
//template<size_t OSIZE>
//ColorStr<TMP_CMP_LEN<SIZE, OSIZE>()>& ColorStr<SIZE>::operator=(ColorStr<OSIZE> &&x) {
    //size_t cut = TMP_CMP_LEN<SIZE, OSIZE>();
    //if (_data != x) {
        //_data = x._data;
        //_data[cut] = '\0';
        //x._data = nullptr;
    //}
    //return *this;
//}


#define ColorStr(x) static_assert(false, "missing ColorStr var name")


} // namespace hdgd

#endif
