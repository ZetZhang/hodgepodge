#include <iostream>
#include <cstdio>
#include <cassert>
#include "hdgd/base/color.h"

#define P(descriptor) do { printf("\n----%s\n\n", descriptor); } while (0)

using namespace hdgd;

// XXX：不好用

void checkForNontypeTemplate() {
    P("Template partial specialization of the ColorStr<0> testing...");

    ColorStr<0> colorStr;
    printf("Color test: %s\n",
            colorStr("Green forecolor & Red backgroundcolor",
                Color::ForeColor::GREEN,
                Color::BackgroundColor::RED_BACK).c_str());

    // Correct: Used the removed move function
    //ColorStr<0> otherColorStr = std::move(colorStr);
    //printf("Color test: %s\n",
            //otherColorStr("Green forecolor & Red backgroundcolor",
                //Color::ForeColor::GREEN,
                //Color::BackgroundColor::RED_BACK).c_str());

    P("Done");
}

void checkForTypeTemplate() {
    P("Normal template ColorStr<size_t> testing...");

    //char buf[9] = "fuckyou";
    //ColorStr<9> colorStr("fuck you");
    //printf("Color test: %s\n",
            //colorStr("Green forecolor & Red backgroundcolor",
                //Color::ForeColor::RED,
                //Color::BackgroundColor::GREEN_BACK).c_str());
    //// ColorStr<19> otherColorStr = std::move(colorStr);// must be error
    //ColorStr<9> otherColorStr(std::move(colorStr));     // ok
    //// ColorStr<9> otherColorStr = std::move(colorStr); // ok
    //printf("Color test: %s\n",
            //otherColorStr("Blue forecolor & White backgroundcolor",
                //Color::ForeColor::BLUE,
                //Color::BackgroundColor::WHITE_BACK).c_str());
    //printf("Color test: %s\n",
            //colorStr("Blue forecolor & Non backgroundcolor",
                //Color::ForeColor::BLUE,
                //Color::BackgroundColor::NONE).c_str());

    ColorStr<32> colorStr("fuck you\nyoumaster\nok\nfsdfsdfas\n", Color::ForeColor::RED, Color::BackgroundColor::GREEN_BACK);
    //ColorStr<32> colorStr("fuck you ", Color::ForeColor::RED, Color::BackgroundColor::GREEN_BACK);

    P("Done");
}

void checkForBasicFColor() {
    P("Basic foreColor display...");

    ColorStr<0> colorStr;
    for (Color::ForeColor fColorIterator = static_cast<Color::ForeColor>(0);
            fColorIterator < Color::ForeColor::NUM_FORE_COLOR;
            fColorIterator = static_cast<Color::ForeColor>(static_cast<unsigned char>(fColorIterator) + 1)) {
        printf("%s",
                // XXX: Will be come back and append the line cut
                colorStr("ForeColor Display...\n",
                    static_cast<Color::ForeColor>(fColorIterator),
                    Color::BackgroundColor::NONE).c_str());
    }

    P("Done");
}

void checkForBasicBGColor() {
    P("Basic backgroundColor display...");

    // FIXME: FUCK
    ColorStr<0> colorStr;
    for (Color::BackgroundColor bGColorIterator = static_cast<Color::BackgroundColor>(0);
            bGColorIterator < Color::BackgroundColor::NUM_BACKGROUND_COLOR;
            bGColorIterator = static_cast<Color::BackgroundColor>(static_cast<unsigned char>(bGColorIterator) + 1)) {
        printf("%s",
                // XXX: Will be come back and append the line cut
                colorStr("BackgroundColor Display...\n",
                    Color::ForeColor::WHITE,
                    static_cast<Color::BackgroundColor>(bGColorIterator)).c_str());
    }

    P("Done");
}

void checkForColorColorPieces() {
    const std::pair<const char*, const char*> pieces_1 = Color::colorPieces(Color::ForeColor::GREEN, Color::BackgroundColor::NONE);
    printf("[%s, %s]\n", pieces_1.first, pieces_1.second);
    assert(strlen(pieces_1.first) == 5/*, "string 1 color piece head"*/);
    assert(strlen(pieces_1.second) == 4/*, "string 2 color piece tail"*/);
    assert((strlen(pieces_1.first) + strlen(pieces_1.second)) == 9/*, "string' length per colorPieces"*/);
    const std::pair<const char*, const char*> pieces_2 = Color::colorPieces(Color::ForeColor::BLUE, Color::BackgroundColor::RED_BACK);
    assert(strlen(pieces_2.first) == 8/*, "string 2 color piece head"*/);
    assert(strlen(pieces_2.second) == 4/*, "string 2 color piece tail"*/);
    assert((strlen(pieces_2.first) + strlen(pieces_2.second)) == 12/*, "string' length per colorPieces"*/);
    printf("{%s, %s}\n", pieces_2.first, pieces_2.second);
}

int main(int argc, const char *argv[])
{
    //checkForNontypeTemplate();
    checkForTypeTemplate();

    //checkForBasicFColor();
    //checkForBasicBGColor();

    //checkForColorColorPieces();
    return 0;
}
