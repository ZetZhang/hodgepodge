#ifndef __HDGD_COLOR_H__
#define __HDGD_COLOR_H__

#include "hdgd/base/noncopyable.h"
#include "hdgd/base/StringPiece.h"

#include <cstdio>
#include <string>
#include <cstring>
#include <array>
#include <vector>

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

    // FIXME: one line
    static const std::pair<const char*, const char*> portion(Color::ForeColor front, Color::BackgroundColor back);
    static /*const*/ std::pair<const char*, const char*>* portionn(Color::ForeColor front, Color::BackgroundColor back);

    struct Portion;
};

// XXX
static const char* ForeColorCode[static_cast<unsigned char>(Color::ForeColor::NUM_FORE_COLOR)] = {
    "30m", "31m", "32m", "33m", "34m", "35m", "36m", "37m",
};

static const char* BackgroundColorCode[static_cast<unsigned char>(Color::BackgroundColor::NUM_BACKGROUND_COLOR)] = {
    "40;", "41;", "42;", "43;", "44;", "45;", "46;", "47;", ""
};

struct Color::Portion {
    Portion(Color::ForeColor fore, Color::BackgroundColor back) : head(new std::string("\033[")), tail(new std::string("\033[0m")){
        head->append(BackgroundColorCode[static_cast<unsigned int>(back)]);
        head->append(ForeColorCode[static_cast<unsigned int>(fore)]);
    }

    const std::pair<const char*, const char*> operator()() {
        return std::pair<const char*, const char*>(head->c_str(), tail->c_str());
    }

    ~Portion() {
        delete head;
        delete tail;
    }

    std::string *head;
    std::string *tail;
};

// Normal
template<size_t SIZE>
class ColorStr : NonCopyable
{
public:
    // XXX

    std::vector<uint32_t> __delegateToCountChar(const char &vc) {
        std::vector<uint32_t> idx;
        for (uint32_t i = 0; i < SIZE; i++)
            if (_data[i] == vc)
                idx.push_back(static_cast<int32_t>(i));
        return idx;
    }

    size_t __delegateToCalcVL(size_t cc) {
        return cc * (strlen(_pieces->head->c_str()) + strlen(_pieces->tail->c_str()));
    }

    void __delegateToINITStr(std::string *str, char sp) {
        std::vector<uint32_t> idx = __delegateToCountChar(sp);
        StringPiece sPtr(_data);
        uint32_t o = 0, pace = 0;
        if (!idx.empty()) {
            for (uint32_t i = 0; i < idx.size(); i++) {
                str->append(_pieces->head->c_str());
                pace = idx[i] - o;
                o = idx[i] + 1;
                str->append(std::string(sPtr.data(), pace));
                sPtr.remove_prefix(pace + 1);
                str->append(_pieces->tail->c_str());
                str->push_back('\n');
            }
        } else {
            str->append(_pieces->head->c_str() + sPtr.as_string() + _pieces->tail->c_str());
        }
    }

    //ColorStr(const char *buf, Color::ForeColor fore, Color::BackgroundColor back) : _pieces(Color::portionn(fore, back)) {
    ColorStr(const char *buf, Color::ForeColor fore, Color::BackgroundColor back) : _pieces(new Color::Portion(fore, back)) {
        ::memmove(_data, buf, SIZE);
        _convertPtr = new std::string;
        __delegateToINITStr(_convertPtr, '\n');
        printf("%ld | %s\n", _convertPtr->size(), (*_convertPtr).c_str());
    }

    ColorStr(const std::string &buf, Color::ForeColor fore, Color::BackgroundColor back) : _pieces(new Color::Portion(fore, back)) {
        ::memmove(_data, buf.c_str(), SIZE);
        _convertPtr = new std::string;
        __delegateToINITStr(_convertPtr, '\n');
    }

    // XXX: 没有意义
    ColorStr(ColorStr &&x) noexcept : _pieces(x._pieces), _convertPtr(x._convertPtr) {
        std::memmove(_data, x._data, SIZE);
        ::memset(_data, '\0', SIZE);
        x._convertPtr = nullptr;
    }

    ColorStr& operator=(ColorStr &&x) noexcept {
        if (this != &x) {
            delete _pieces;
            _pieces = x._pieces;
            std::memmove(_data, x._data, SIZE);
            ::memset(_data, '\0', SIZE);
            delete _convertPtr;
            _convertPtr = x._convertPtr;
            x._convertPtr = nullptr;
        }
        return *this;
    }

    ~ColorStr() noexcept {
        if (_convertPtr != nullptr) {
            delete _convertPtr;
        }
        ::memset(_data, '\0', SIZE);
        delete _pieces;
    }

    const std::string operator()() {
        return *_convertPtr;
    }

    // FIXME: should be return the string piece
    const std::string operator()(const char *buf, Color::ForeColor fore, Color::BackgroundColor back) {
        //const std::pair<const std::string, const std::string> pieces = Color::portion(front, back);
        const std::pair<const char*, const char*> pieces = Color::portion(fore, back);
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
    Color::Portion *_pieces;
    char _data[SIZE];
    std::string *_convertPtr;

    ColorStr() = delete;
};

// Partial
// FIXME: Something wrong
template<>
class ColorStr<0> : NonCopyable
{
public:
    ColorStr() = default;

    // XXX:只适合单行
    const std::string operator()(const char *buf, Color::ForeColor fore, Color::BackgroundColor back) {
        const std::pair<const char*, const char*> pieces = Color::portion(fore, back);
        return std::string(std::string(pieces.first) + buf + std::string(pieces.second));
    }
private:
    ColorStr(ColorStr &&) noexcept = delete;
    ColorStr& operator=(ColorStr &&) noexcept = delete;
};



#define ColorStr(x) static_assert(false, "missing ColorStr var name")


} // namespace hdgd

#endif
