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

    //ColorStr<32> colorStr("fuck you\nyoumaster\nok\nfsdfsdfas\n", Color::ForeColor::RED, Color::BackgroundColor::GREEN_BACK);
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
    //const std::pair<const char*, const char*> pieces_1 = Color::colorPieces(Color::ForeColor::GREEN, Color::BackgroundColor::NONE);
    //printf("[%s, %s]\n", pieces_1.first, pieces_1.second);
    //assert(strlen(pieces_1.first) == 5[>, "string 1 color piece head"<]);
    //assert(strlen(pieces_1.second) == 4[>, "string 2 color piece tail"<]);
    //assert((strlen(pieces_1.first) + strlen(pieces_1.second)) == 9[>, "string' length per colorPieces"<]);
    //const std::pair<const char*, const char*> pieces_2 = Color::colorPieces(Color::ForeColor::BLUE, Color::BackgroundColor::RED_BACK);
    //assert(strlen(pieces_2.first) == 8[>, "string 2 color piece head"<]);
    //assert(strlen(pieces_2.second) == 4[>, "string 2 color piece tail"<]);
    //assert((strlen(pieces_2.first) + strlen(pieces_2.second)) == 12[>, "string' length per colorPieces"<]);
    //printf("{%s, %s}\n", pieces_2.first, pieces_2.second);
}

// FIXME: 垃圾
void newCheck() {
    // 链式build
    Color::ColorPiece *piece = Color::ColorPiece::New()
        ->setForeColor(Color::ForeColor::BLACK)
        ->setBackgroundColor(Color::BackgroundColor::WHITE_BACK)
        //->setHighLight()
        //->setUnderLine()
        ->setFlash()
        //->setReverseVideo()
        //->setBlank()
        ->build();
    // 取头尾两块颜色格式片
    std::cout << piece->head() << "piece testing line..." << piece->tail() << std::endl;
    // pointer：同一个地址
    Color::ColorPiece *piece1(std::move(piece));
    std::cout << piece1->head() << "piece1 testing line..." << piece1->tail() << std::endl;

    delete piece1;
    // FIXME: ERROR: move construction by pointer
    //Color::ColorPiece piece2(std::move(*piece1));

    Color::ColorPiece piece3;
    piece3.setForeColor(Color::ForeColor::BLUE);
    piece3.setBackgroundColor(Color::BackgroundColor::YELLOW_BACK);
    piece3.setFlash();
    piece3.build();
    std::cout << piece3.head() << "piece3 testing line..." << piece3.tail() << std::endl;

    // move construction
    Color::ColorPiece piece4(std::move(piece3));
    piece4.reset(Color::ForeColor::BLUE, Color::BackgroundColor::BLUE_BACK);
    piece4.setFlash(false);
    piece4.condBuild();
    std::cout << piece4.head() << "piece4 testing line..." << piece4.tail() << std::endl;
    // move assigement
    Color::ColorPiece piece5 = std::move(piece4);
    piece5.resetAll();
    piece5.setFlash(true);
    piece5.condBuild();
    std::cout << piece5.head() << "piece5 testing line..." << piece4.tail() << std::endl;
}

int main(int argc, const char *argv[])
{
    //checkForNontypeTemplate();
    checkForTypeTemplate();

    //checkForBasicFColor();
    //checkForBasicBGColor();

    //checkForColorColorPieces();

    newCheck();
    return 0;
}
