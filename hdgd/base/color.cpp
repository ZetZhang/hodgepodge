#include "hdgd/base/color.h"

#include <cstdlib>

namespace hdgd
{

Color::ColorPiece::ColorPiece() : _head(new std::string("\033[")), _tail("\033[0m") { }

//Color::ColorPiece::ColorPiece(Color::ColorPiece *cp) : _head(new std::string("\033[")), _tail("\033[0m"){
    //const char *back = BackgroundColorCode[static_cast<unsigned int>(back)];
    //const char *fore = ForeColorCode[static_cast<unsigned int>(fore)];
    //_head = static_cast<char*>(::malloc((strlen(back) + strlen(fore) + 2) * sizeof(char)));
    //::memmove(_head, "\033[", 2);
    //::strncat(_head, back, strlen(back));
    //::strncat(_head, fore, strlen(fore));
//}

Color::ColorPiece::ColorPiece(ColorPiece &&x) noexcept {

}

Color::ColorPiece& Color::ColorPiece::operator=(ColorPiece &&x) noexcept {
    return *this;
}

void Color::ColorPiece::reset(Color::ForeColor fore, Color::BackgroundColor back) {
    _colorPieceFL = 0;
}

#define MANUFACTURE_CONFIGURATION(discrimination, catstr, type, bit)            \
    inline Color::ColorPiece& Color::ColorPiece::set##discrimination (type) {   \
        if (!__HDGD_GET_BIT_STAT(_colorPieceFL, bit)) {                         \
            if (!_colorPieceFL) _head->push_back(';');                          \
            _head->append( catstr );                                            \
            __HDGD_SET_BIT_STAT(_colorPieceFL, bit);                            \
        }                                                                       \
        return *this;                                                           \
    }

#define MANUFACTURE_CONFIGURATION_R(discrimination, bit)                            \
    inline Color::ColorPiece& Color::ColorPiece::set##discrimination (bool flag) {  \
        __HDGD_U8_COND_SET(_colorPieceFL, bit, flag);                               \
        return *this;                                                               \
    }

MANUFACTURE_CONFIGURATION_R(ForeColor, 1);
MANUFACTURE_CONFIGURATION_R(BackgroundColor, 2);
MANUFACTURE_CONFIGURATION_R(HightLight, 3);
MANUFACTURE_CONFIGURATION_R(UnderLine, 4);
MANUFACTURE_CONFIGURATION_R(Flash, 5);
MANUFACTURE_CONFIGURATION_R(ReverseVideo, 6);
MANUFACTURE_CONFIGURATION_R(Blank, 7);

MANUFACTURE_CONFIGURATION(ForeColor, ForeColorCode[static_cast<unsigned int>(fore)], Color::ForeColor fore, 1);
MANUFACTURE_CONFIGURATION(BackgroundColor, BackgroundColorCode[static_cast<unsigned int>(back)], Color::BackgroundColor back, 2);
MANUFACTURE_CONFIGURATION(HightLight, "1", __parameter_unused(), 3);
MANUFACTURE_CONFIGURATION(UnderLine, "4", __parameter_unused(), 4);
MANUFACTURE_CONFIGURATION(Flash, "5", __parameter_unused(), 5);
MANUFACTURE_CONFIGURATION(ReverseVideo, "7", __parameter_unused(), 6);
MANUFACTURE_CONFIGURATION(Blank, "8", __parameter_unused(), 7);

void Color::ColorPiece::setNo(bool flag) {
}

Color::ColorPiece& Color::ColorPiece::build() {
    _head->push_back('m');
    return *this;
}

const std::pair<const char*, const char*> Color::ColorPiece::operator()() {
    return std::pair<const char*, const char*>(_head->c_str(), _tail);
}

const std::pair<const char*, const char*> Color::ColorPiece::getColorPiece() {
    return operator()();
}

Color::ColorPiece::~ColorPiece() {
    //::free(_head);
    delete _head;
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
