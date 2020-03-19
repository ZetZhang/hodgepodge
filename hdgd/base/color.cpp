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

namespace hdgd
{

Color::ColorPiece::ColorPiece() : _colorPieceFL(0), _head(new std::string("\033[")), _tail("\033[0m") { }

// FIXME
Color::ColorPiece::ColorPiece(ColorPiece &&x) noexcept : _colorPieceFL(x._colorPieceFL), _head(x._head), _tail(x._tail) {
    x._colorPieceFL = 0;
    x._head = nullptr;
    x._tail = nullptr;
}

// FIXME
Color::ColorPiece& Color::ColorPiece::operator=(ColorPiece &&x) noexcept {
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

void Color::ColorPiece::reset(Color::ForeColor fore, Color::BackgroundColor back) {
    if (_colorPieceFL != 0) {
        _head->resize(2);
        _HDGD_SET_BIT_F(_colorPieceFL, _HDGD_BIT(7));
        _HDGD_SET_BIT_F(_colorPieceFL, _HDGD_BIT(0));
        _HDGD_SET_BIT_F(_colorPieceFL, _HDGD_BIT(1));
        setForeColor(fore)->setBackgroundColor(Color::BackgroundColor::RED_BACK);
    }
}

void Color::ColorPiece::resetAll() {
    _head->resize(2);
    _colorPieceFL = 0;
}

// 函数生成宏
#define MANUFACTURE_CONFIGURATION(discrimination, catstr, type, bit)    \
    Color::ColorPiece* Color::ColorPiece::set##discrimination (type) {  \
        if (!_HDGD_GET_BIT_STAT(_colorPieceFL, _HDGD_BIT(bit))) {       \
            if (_colorPieceFL != 0) _head->push_back(';');              \
            _head->append( catstr );                                    \
            _HDGD_SET_BIT_T(_colorPieceFL, _HDGD_BIT(bit));             \
        }                                                               \
        return this;                                                    \
    }

#define MANUFACTURE_CONFIGURATION_R(discrimination, bit)                    \
    Color::ColorPiece* Color::ColorPiece::set##discrimination (bool flag) { \
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

MANUFACTURE_CONFIGURATION(ForeColor, ForeColorCode[static_cast<unsigned int>(fore)], Color::ForeColor fore, 0);
MANUFACTURE_CONFIGURATION(BackgroundColor, BackgroundColorCode[static_cast<unsigned int>(back)], Color::BackgroundColor back, 1);
MANUFACTURE_CONFIGURATION(HighLight, "1", __parameter_unused(), 2);
MANUFACTURE_CONFIGURATION(UnderLine, "4", __parameter_unused(), 3);
MANUFACTURE_CONFIGURATION(Flash, "5", __parameter_unused(), 4);
MANUFACTURE_CONFIGURATION(ReverseVideo, "7", __parameter_unused(), 5);
MANUFACTURE_CONFIGURATION(Blank, "8", __parameter_unused(), 6);

// XXX: build时enable位不设位保持状态，供condBuild重新生成
Color::ColorPiece* Color::ColorPiece::build() {
    if (!_HDGD_GET_BIT_STAT(_colorPieceFL, _HDGD_BIT(7))) {
        _head->push_back('m');
        _HDGD_SET_BIT_T(_colorPieceFL, _HDGD_BIT(7));
    }
    return this;
}

Color::ColorPiece* Color::ColorPiece::condBuild() {
    // 输出属性设置Code
    const char *tCode = "14578";
    if (_colorPieceFL == 0)
        _head->append("0m");
    else if (!_HDGD_GET_BIT_STAT(_colorPieceFL, _HDGD_BIT(7))) {
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

const std::pair<const char*, const char*> Color::ColorPiece::operator()() {
    return _HDGD_GET_BIT_STAT(_colorPieceFL, _HDGD_BIT(7))
        ? std::pair<const char*, const char*>(_head->c_str(), _tail)
        : std::pair<const char*, const char*>("", "");
}

const std::pair<const char*, const char*> Color::ColorPiece::getColorPiece() {
    return operator()();
}

Color::ColorPiece::~ColorPiece() {
    if (_head) {
        delete _head;
        _head = nullptr;
    }
    _tail = nullptr;
}

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
    std::string *head = new std::string("\033[");
    head->append(BackgroundColorCode[static_cast<unsigned int>(back)]);
    head->append(ForeColorCode[static_cast<unsigned int>(front)]);
    return std::make_pair(head->c_str(), "\033[0m");
}

std::pair<const char*, const char*>* Color::portionn(Color::ForeColor front, Color::BackgroundColor back) {
    std::pair<const char*, const char*> *ret = nullptr;
    std::string *head = new std::string("\033[");
    //std::string head("\033[");
    head->append(BackgroundColorCode[static_cast<unsigned int>(back)]);
    head->append(ForeColorCode[static_cast<unsigned int>(front)]);
    return new std::pair<const char*, const char*>(head->c_str(), "\033[0m");
}
