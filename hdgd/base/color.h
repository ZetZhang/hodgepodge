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

static void PRI(const char *buf)
{
    char ch;
    char *i = const_cast<char*>(buf);
    printf("[");
    while ((ch = *i++) != '\0')
        printf("%c,", static_cast<char>(ch));
    printf("]\n");
}

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

    // 内部类
    class ColorPiece;
};

class Color::ColorPiece : NonCopyable {
public:
    // Color::ColorPiece::New()->set()->set()->set()->set()->build();
    static ColorPiece* New() { ColorPiece *ret = new ColorPiece(); return ret; }
    ColorPiece();
    ColorPiece(Color::ForeColor fore, Color::BackgroundColor back);
    // move
    ColorPiece(ColorPiece &&x) noexcept;
    ColorPiece& operator=(ColorPiece &&x) noexcept;

    const std::pair<const char*, const char*> operator()();
    const std::pair<const char*, const char*> getColorPiece();
    void reset();
    void resetAll();
    void reset(Color::ForeColor fore, Color::BackgroundColor back);

    ColorPiece* setForeColor(Color::ForeColor fore);
    ColorPiece* setBackgroundColor(Color::BackgroundColor back);

    ColorPiece* setHighLight();
    ColorPiece* setUnderLine();
    ColorPiece* setFlash();
    ColorPiece* setReverseVideo();
    ColorPiece* setBlank();
    ColorPiece* build();

    ColorPiece* setHighLight(bool flag);
    ColorPiece* setUnderLine(bool flag);
    ColorPiece* setFlash(bool flag);
    ColorPiece* setReverseVideo(bool flag);
    ColorPiece* setBlank(bool flag);
    ColorPiece* condBuild();

    bool isReadable();

    const char* head() { return _head->c_str(); }
    const char* tail() { return _tail; }

    ~ColorPiece();

private:
    uint8_t _colorPieceFL;
    std::string *_head;
    char *_tail;
};

// XXX
static const char* ForeColorCode[static_cast<unsigned char>(Color::ForeColor::NUM_FORE_COLOR)] = {
    "30", "31", "32", "33", "34", "35", "36", "37",
};

static const char* BackgroundColorCode[static_cast<unsigned char>(Color::BackgroundColor::NUM_BACKGROUND_COLOR)] = {
    "40", "41", "42", "43", "44", "45", "46", "47", "48"/*?*/,
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

    ColorStr(const char *buf, Color::ForeColor fore, Color::BackgroundColor back) : _pieces(Color::ColorPiece::New()
            ->setForeColor(fore)
            ->setBackgroundColor(back)
            ->build()), _convertPtr(new std::string){
        fromString(buf);
        __delegateToINITStr(_convertPtr, '\n');
    }

    ColorStr(const std::string &buf, Color::ForeColor fore, Color::BackgroundColor back) : _pieces(Color::ColorPiece::New()
            ->setForeColor(fore)
            ->setBackgroundColor(back)
            ->build()), _convertPtr(new std::string) {
        fromString(buf.c_str());
        __delegateToINITStr(_convertPtr, '\n');
    }

    // XXX: 没有意义
    ColorStr(ColorStr &&x) noexcept : _pieces(x._pieces), _convertPtr(x._convertPtr) {
        std::memmove(_data, x._data, SIZE);
        ::memset(x._data, '\0', SIZE);
        x._convertPtr = nullptr;
        x._pieces = nullptr;
    }

    ColorStr& operator=(ColorStr &&x) noexcept {
        if (this != &x) {
            //delete _pieces;
            _pieces = x._pieces;
            std::memmove(_data, x._data, SIZE);
            ::memset(x._data, '\0', SIZE);
            delete _convertPtr;
            _convertPtr = x._convertPtr;
            x._convertPtr = nullptr;
            x._pieces = nullptr;
        }
        return *this;
    }

    ~ColorStr() noexcept {
        if (_convertPtr != nullptr) delete _convertPtr;
        if (_pieces != nullptr) delete _pieces;
        ::memset(_data, '\0', SIZE);
    }

    const std::string operator()() {
        return *_convertPtr;
    }

    void reColor(Color::ForeColor fore, Color::BackgroundColor back) {
        _pieces->reset(fore, back);
        _pieces->build();
        __delegateToINITStr(_convertPtr, '\n');
    }

    void fromString(const char *buf) {
        int cut = std::min(SIZE, strlen(buf));
        ::memmove(_data, buf, cut);
        _data[cut] = '\0';
    }

    const char* originalString() {
        return _data;
    }

    const std::string toColoredString() {
        return *_convertPtr;
    }

    const char* toColoredCStr() {
        return (*_convertPtr).c_str();
    }

    const std::string toColoredString(Color::ForeColor fore, Color::BackgroundColor back) {
        reColor(fore, back);
        // POV?
        return *_convertPtr;
    }

    const char* toColoredCStr(Color::ForeColor fore, Color::BackgroundColor back) {
        reColor(fore, back);
        return (*_convertPtr).c_str();
    }
private:
    Color::ColorPiece *_pieces;
    char _data[SIZE];
    std::string *_convertPtr;

    ColorStr() = delete;
};

// Partial
template<>
class ColorStr<0> : NonCopyable
{
public:
    ColorStr() = default;

    // XXX:只适合单行
    const std::string operator()(const char *buf, Color::ForeColor fore, Color::BackgroundColor back) {
        const std::pair<const char*, const char*> pieces = Color::portion(fore, back);
        return std::string(pieces.first) + buf + std::string(pieces.second);
    }
private:
    ColorStr(ColorStr &&) noexcept = delete;
    ColorStr& operator=(ColorStr &&) noexcept = delete;
};



#define ColorStr(x) static_assert(false, "missing ColorStr var name")


} // namespace hdgd

#endif
