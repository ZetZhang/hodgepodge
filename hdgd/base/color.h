#ifndef __HDGD_COLOR_H__
#define __HDGD_COLOR_H__

#include "hdgd/base/noncopyable.h"
#include "hdgd/base/StringPiece.h"
#include "hdgd/base/bit_operation.h"

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
    static const std::pair<const char*, const char*> portion(Color::ForeColor fore, Color::BackgroundColor back);
    static /*const*/ std::pair<const char*, const char*>* portionn(Color::ForeColor fore, Color::BackgroundColor back);

    class ColorPiece;
};

class Color::ColorPiece {
public:
    // Color::ColorPiece::New().set().set().set().set().build();
    static ColorPiece& New() { ColorPiece *ret = new ColorPiece(); return *ret; }
    ColorPiece();
    ColorPiece(Color::ForeColor fore, Color::BackgroundColor back);
    ColorPiece(ColorPiece &&x) noexcept;
    ColorPiece& operator=(ColorPiece &&x) noexcept;

    const std::pair<const char*, const char*> operator()();
    const std::pair<const char*, const char*> getColorPiece();
    void reset(Color::ForeColor fore, Color::BackgroundColor back);

    ColorPiece& setForeColor(Color::ForeColor fore);
    ColorPiece& setBackgroundColor(Color::BackgroundColor back);
    ColorPiece& setForeColor(bool flag);
    ColorPiece& setBackgroundColor(bool flag);
    ColorPiece& setHightLight(bool flag);
    ColorPiece& setUnderLine(bool flag);
    ColorPiece& setFlash(bool flag);
    ColorPiece& setReverseVideo(bool flag);
    ColorPiece& setBlank(bool flag);
    ColorPiece& build();
    void setNo(bool flag);

    ColorPiece& setHightLight();
    ColorPiece& setUnderLine();
    ColorPiece& setFlash();
    ColorPiece& setReverseVideo();
    ColorPiece& setBlank();

    const char* head() { return _head->c_str(); }
    const char* tail() { return _tail; }
    ~ColorPiece();
private:
    uint8_t _colorPieceFL;
    //char *_head;
    std::string *_head;
    char *_tail;
};

// XXX
static const char* ForeColorCode[static_cast<unsigned char>(Color::ForeColor::NUM_FORE_COLOR)] = {
    "30", "31", "32", "33", "34", "35", "36", "37",
};

static const char* BackgroundColorCode[static_cast<unsigned char>(Color::BackgroundColor::NUM_BACKGROUND_COLOR)] = {
    "40", "41", "42", "43", "44", "45", "46", "47", "",
};

//static const char* DisplayEffectBitCode[7] = {
    //"0", "1", "4", "5", "7", "8"
//}

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
        return cc * (strlen(_pieces->head()) + strlen(_pieces->tail()));
    }

    void __delegateToINITStr(std::string *str, char sp) {
        std::vector<uint32_t> idx = __delegateToCountChar(sp);
        StringPiece sPtr(_data);
        uint32_t o = 0, pace = 0;
        if (!idx.empty()) {
            for (uint32_t i = 0; i < idx.size(); i++) {
                str->append(_pieces->head());
                pace = idx[i] - o;
                o = idx[i] + 1;
                str->append(std::string(sPtr.data(), pace));
                sPtr.remove_prefix(pace + 1);
                str->append(_pieces->tail());
                str->push_back('\n');
            }
        } else {
            str->append(_pieces->head() + sPtr.as_string() + _pieces->tail());
        }
    }

    ColorStr(const char *buf, Color::ColorPiece *cp) : _pieces(cp) {
        ::memmove(_data, buf, SIZE);
        _convertPtr = new std::string;
        __delegateToINITStr(_convertPtr, '\n');
        printf("%ld | %s\n", _convertPtr->size(), (*_convertPtr).c_str());
    }

    ColorStr(const std::string &buf, Color::ColorPiece *cp) : _pieces(cp) {
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
            //delete _pieces;
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
        //delete _pieces;
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

    const char* originalString() {
        return _data;
    }

    const std::string toColoredString(Color::ForeColor front, Color::BackgroundColor back) {
        //if (_pieces != nullptr) {
            //delete _pieces;
        //}
        if (!strlen(_data)) {
            /* XXX: There is no zero length anymore */
            return nullptr;
        } else {
            return operator()(_data, front, back);
        }
    }
private:
    Color::ColorPiece *_pieces;
    //std::pair<const char*, const char*> _pieces;
    char _data[SIZE];
    std::string *_convertPtr;
    char *convertPtr;
    //std::vector<uint32_t> _charsIndex;

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
