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

#if 0
static void PRI(const char *buf)
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

//struct Color
namespace color
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
        NONE,
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

    // 内部类
    class ColorPiece;

    // FIXME: one line
    static const std::pair<const char*, const char*> Portion(ForeColor fore, BackgroundColor back);
};

class color::ColorPiece : NonCopyable {
public:
    // color::ColorPiece::New()->set()->set()->set()->set()->build();
    static ColorPiece* New() { ColorPiece *ret = new ColorPiece(); return ret; }
    ColorPiece();
    ColorPiece(color::ForeColor fore, color::BackgroundColor back);
    // move
    ColorPiece(ColorPiece &&x) noexcept;
    ColorPiece& operator=(ColorPiece &&x) noexcept;

    const std::pair<const char*, const char*> operator()();
    const std::pair<const char*, const char*> getColorPiece();
    void reset();
    void resetAll();
    void reset(color::ForeColor fore, color::BackgroundColor back);

    ColorPiece* setForeColor(color::ForeColor fore);
    ColorPiece* setBackgroundColor(color::BackgroundColor back);

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

    const char* head() { return _head->data(); }
    const char* tail() { return _tail; }

    ~ColorPiece();

private:
    uint8_t _colorPieceFL;
    std::string *_head;
    const char *_tail;
};

const std::pair<const char*, const char*> color::Portion(ForeColor fore, BackgroundColor back) {
    ColorPiece cp;
    cp.setForeColor(fore);
    cp.setBackgroundColor(back);
    cp.build();
    return std::make_pair(cp.head(), cp.tail());
}

// Normal
template<size_t SIZE>
class ColorStr : NonCopyable
{
private:
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
        StringPiece hP(_data.data());
        uint32_t o = 0, pace = 0;
        if (!idx.empty()) {
            if (str->size() >= static_cast<size_t>(hP.size()))
                str->clear();
            for (uint32_t i = 0; i < idx.size(); i++) {
                str->append(_pieces->head());
                pace = idx[i] - o;
                o = idx[i] + 1;
                str->append(std::string(hP.data(), pace));
                hP.remove_prefix(pace + 1);
                str->append(_pieces->tail());
                str->push_back('\n');
            }
            if (!hP.empty()) {
                str->append(_pieces->head());
                str->append(hP.data());
                str->append(_pieces->tail());
            }
        } else {
            str->append(_pieces->head() + hP.as_string() + _pieces->tail());
        }
    }

public:
    ColorStr(const char *buf, color::ForeColor fore, color::BackgroundColor back) : _data(buf), _pieces(
            color::ColorPiece::New()
            ->setForeColor(fore)
            ->setBackgroundColor(back)
            ->build()), _convertPtr(new std::string){
        __delegateToINITStr(_convertPtr, '\n');
    }

    ColorStr(const std::string &buf, color::ForeColor fore, color::BackgroundColor back) : _data(buf), _pieces(
            color::ColorPiece::New()
            ->setForeColor(fore)
            ->setBackgroundColor(back)
            ->build()), _convertPtr(new std::string) {
        __delegateToINITStr(_convertPtr, '\n');
    }

    // XXX: 没有意义
    ColorStr(ColorStr &&x) noexcept : _data(x._data), _pieces(x._pieces), _convertPtr(x._convertPtr) {
        x._convertPtr = nullptr;
        x._pieces = nullptr;
    }

    ColorStr& operator=(ColorStr &&x) noexcept {
        if (this != &x) {
            _data = x._data;
            _pieces = x._pieces;
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
    }

    const std::string operator()() {
        return *_convertPtr;
    }

    void reColor(color::ForeColor fore, color::BackgroundColor back) {
        _pieces->reset(fore, back);
        _pieces->build();
        __delegateToINITStr(_convertPtr, '\n');
    }

    void fromString(const char *buf) {
        size_t cut = std::min(SIZE, strlen(buf));
        _data.set(buf, cut);
    }

    void fromString(const std::string &buf) {
        size_t cut = std::min(SIZE, buf.size());
        _data.set(buf.data(), cut);
    }

    const char* originalString() {
        //return _data;
        return _data.data();
    }

    const std::string toColoredString() {
        return *_convertPtr;
    }

    const char* toColoredCStr() {
        return (*_convertPtr).c_str();
    }

    const std::string toColoredString(color::ForeColor fore, color::BackgroundColor back) {
        reColor(fore, back);
        // POV?
        return *_convertPtr;
    }

    const char* toColoredCStr(color::ForeColor fore, color::BackgroundColor back) {
        reColor(fore, back);
        return (*_convertPtr).c_str();
    }

    friend std::ostream& operator<<(std::ostream& os, const ColorStr &x) {
        os << *x._convertPtr;
        return os;
    }

private:
    StringPiece _data;
    color::ColorPiece *_pieces;
    //char _data[SIZE];
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
    const std::string operator()(const char *buf, color::ForeColor fore, color::BackgroundColor back) {
        using namespace std;
        const pair<const char*, const char*> pieces = color::Portion(fore, back);
        return string(string(pieces.first) + buf + string(pieces.second));
    }

private:
    ColorStr(ColorStr &&) noexcept = delete;
    ColorStr& operator=(ColorStr &&) noexcept = delete;
};



#define ColorStr(x) static_assert(false, "missing ColorStr var name")


} // namespace hdgd

#endif
