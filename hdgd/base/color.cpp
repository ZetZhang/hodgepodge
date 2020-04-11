#include "hdgd/base/color.h"

#include <cstdlib>

//  7           6           5               4           3           2               1               0
// enable | blanking | reversedisplay | flashing | underline | highlight | backgroundcolorSet | forecolorSet |
#define BITSH(U8, STR) do {     \
    printf("%*s|", 20, STR);    \
    for (int i = 7; i >= 0; i--)\
        printf("%d|",           \
                _HDGD_GET_BIT_STAT(U8, _HDGD_BIT(i)) ? 1 : 0); \
    printf("\n");               \
} while (0)

namespace hdgd{

namespace color
{

// XXX
static const char* ForeColorCode[static_cast<unsigned char>(color::ForeColor::NUM_FORE_COLOR)] = {
    "30", "31", "32", "33", "34", "35", "36", "37", "39"
};

static const char* BackgroundColorCode[static_cast<unsigned char>(color::BackgroundColor::NUM_BACKGROUND_COLOR)] = {
    "40", "41", "42", "43", "44", "45", "46", "47", "49",
};

ColorPiece::ColorPiece() : _colorPieceFL(0), _head(new std::string("\033[")), _tail("\033[0m") { }

// FIXME
ColorPiece::ColorPiece(ColorPiece &&x) noexcept : _colorPieceFL(x._colorPieceFL), _head(x._head), _tail(x._tail) {
    x._colorPieceFL = 0;
    x._head = nullptr;
    x._tail = nullptr;
}

// FIXME
ColorPiece& ColorPiece::operator=(ColorPiece &&x) noexcept {
    if (this != &x) {
        _colorPieceFL = x._colorPieceFL;
        delete _head;
        _head = x._head;
        _tail = x._tail;
        x._colorPieceFL = 0;
        x._head = nullptr;
        x._tail = nullptr;
    }
    return *this;
}

void ColorPiece::reset(ForeColor fore, BackgroundColor back) {
    if (_colorPieceFL != 0) {
        _head->resize(2);
        _HDGD_SET_BIT_F(_colorPieceFL, _HDGD_BIT(7));
        _HDGD_SET_BIT_F(_colorPieceFL, _HDGD_BIT(0));
        _HDGD_SET_BIT_F(_colorPieceFL, _HDGD_BIT(1));
        setForeColor(fore)->setBackgroundColor(BackgroundColor::RED_BACK);
    }
}

void ColorPiece::resetAll() {
    if (_colorPieceFL != 0) {
        _head->resize(2);
        _colorPieceFL = 0;
    }
}

bool ColorPiece::isReadable() {
    return _HDGD_GET_BIT_STAT(_colorPieceFL, _HDGD_BIT(7)) == 1;
}

// 函数生成宏
#define MANUFACTURE_CONFIGURATION(discrimination, catstr, type, bit)    \
    ColorPiece* ColorPiece::set##discrimination (type) {  \
        if (!_HDGD_GET_BIT_STAT(_colorPieceFL, _HDGD_BIT(bit))) {       \
            if (_colorPieceFL != 0) _head->push_back(';');              \
            _head->append( catstr );                                    \
            _HDGD_SET_BIT_T(_colorPieceFL, _HDGD_BIT(bit));             \
        }                                                               \
        return this;                                                    \
    }

#define MANUFACTURE_CONFIGURATION_R(discrimination, bit)                    \
    ColorPiece* ColorPiece::set##discrimination (bool flag) {               \
        _HDGD_U8_COND_SET_BIT(_colorPieceFL, _HDGD_BIT(bit), flag);         \
        return this;                                                        \
    }

//MANUFACTURE_CONFIGURATION_R(ForeColor, 0);
//MANUFACTURE_CONFIGURATION_R(BackgroundColor, 1);
MANUFACTURE_CONFIGURATION_R(HighLight, 2);
MANUFACTURE_CONFIGURATION_R(UnderLine, 3);
MANUFACTURE_CONFIGURATION_R(Flash, 4);
MANUFACTURE_CONFIGURATION_R(ReverseVideo, 5);
MANUFACTURE_CONFIGURATION_R(Blank, 6);

MANUFACTURE_CONFIGURATION(ForeColor, ForeColorCode[static_cast<unsigned int>(fore)], ForeColor fore, 0);
MANUFACTURE_CONFIGURATION(BackgroundColor, BackgroundColorCode[static_cast<unsigned int>(back)], BackgroundColor back, 1);
MANUFACTURE_CONFIGURATION(HighLight, "1", __parameter_unused(), 2);
MANUFACTURE_CONFIGURATION(UnderLine, "4", __parameter_unused(), 3);
MANUFACTURE_CONFIGURATION(Flash, "5", __parameter_unused(), 4);
MANUFACTURE_CONFIGURATION(ReverseVideo, "7", __parameter_unused(), 5);
MANUFACTURE_CONFIGURATION(Blank, "8", __parameter_unused(), 6);

// XXX: build时enable位不设位保持状态，供condBuild重新生成
ColorPiece* ColorPiece::build() {
    if (!isReadable()) {
        _head->push_back('m');
        _HDGD_SET_BIT_T(_colorPieceFL, _HDGD_BIT(7));
    }
    return this;
}

ColorPiece* ColorPiece::condBuild() {
    // 输出属性设置Code
    const char *tCode = "14578";
    if (_colorPieceFL == 0)
        _head->append("0m");
    else if (!isReadable()) {
        for (size_t i = 0; i < strlen(tCode); i++)
            // 略过主体颜色设置占位
            if (_HDGD_GET_BIT_STAT(_colorPieceFL, _HDGD_BIT((i + 2)))) {
                _head->push_back(';');
                _head->push_back(tCode[i]);
            }
        _head->push_back('m');
        _HDGD_SET_BIT_T(_colorPieceFL, _HDGD_BIT(7));
    }
    return this;
}

const std::pair<const char*, const char*> ColorPiece::operator()() {
    return _HDGD_GET_BIT_STAT(_colorPieceFL, _HDGD_BIT(7)) != 0
        ? std::pair<const char*, const char*>(_head->data(), _tail)
        : std::pair<const char*, const char*>("", "");
}

const std::pair<const char*, const char*> ColorPiece::getColorPiece() {
    return operator()();
}

ColorPiece::~ColorPiece() {
    if (_head) {
        delete _head;
        _head = nullptr;
    }
    _tail = nullptr;
}


} // color

} // namespace hdgd


