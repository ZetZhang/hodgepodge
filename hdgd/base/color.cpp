#include "hdgd/base/color.h"

namespace hdgd
{

Color::ColorPieces::ColorPieces(Color::ForeColor fore, Color::BackgroundColor back) : head(std::string("\033[")), tail(std::string("\033[0m")){
    head.append(BackgroundColorCode[static_cast<unsigned int>(back)]);
    head.append(ForeColorCode[static_cast<unsigned int>(fore)]);
}

const std::pair<const char*, const char*> Color::ColorPieces::operator()() {
    return std::pair<const char*, const char*>(head.c_str(), tail.c_str());
}

} // namespace hdgd


using namespace hdgd;


// FIXME:需要区分有无底色，无底色5，底色8，结尾4。则每个\r\n需要塞9+1个字节或12+1个字节
// Need a string piece
// FIXME: out of data
//const std::pair<const char*, const char*> Color::colorPieces(Color::ForeColor front, Color::BackgroundColor back) {
    //// if back == "" { hasn't bg } else { has bg }
    //using std::string;
    //const std::string head("\033["
            //+ string(BackgroundColorCode[static_cast<unsigned int>(back)])
            //+ string(ForeColorCode[static_cast<unsigned int>(front)]));
    //const char *tail = "\033[0m\r\n";
    //return std::make_pair(head.c_str(), tail);
//}

const std::pair<const char*, const char*> Color::colorPieces(Color::ForeColor front, Color::BackgroundColor back) {
    std::string *head = new std::string("\033[");
    head->append(BackgroundColorCode[static_cast<unsigned int>(back)]);
    head->append(ForeColorCode[static_cast<unsigned int>(front)]);
    return std::make_pair(head->c_str(), "\033[0m");
}

std::pair<const char*, const char*>* Color::colorPiecesn(Color::ForeColor front, Color::BackgroundColor back) {
    std::pair<const char*, const char*> *ret = nullptr;
    std::string *head = new std::string("\033[");
    //std::string head("\033[");
    head->append(BackgroundColorCode[static_cast<unsigned int>(back)]);
    head->append(ForeColorCode[static_cast<unsigned int>(front)]);
    return new std::pair<const char*, const char*>(head->c_str(), "\033[0m");
}
