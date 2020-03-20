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
                Color::BackgroundColor::RED_BACK));

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

    ColorStr<12> colorStr("test a\nb\nc\nd", Color::ForeColor::BLUE, Color::BackgroundColor::YELLOW_BACK);
    std::cout << colorStr.originalString() << " -> " << colorStr.toColoredString() << std::endl;
    ColorStr<12> moveStr(std::move(colorStr));  // move construction
    std::cout << moveStr.originalString() << " -> " << moveStr.toColoredString() <<
        " -> " << moveStr.toColoredString(Color::ForeColor::YELLOW, Color::BackgroundColor::GREEN_BACK) << std::endl;

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
                    Color::BackgroundColor::NONE));
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
                    static_cast<Color::BackgroundColor>(bGColorIterator)));
    }

    P("Done");
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

    std::pair<const char*, const char*> piece_trait = piece1->getColorPiece();
    delete piece1;

    std::cout << piece_trait.first << "piece trait testing line..." << piece_trait.second << std::endl;
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
    std::pair<const char*, const char*> piecePair = piece5.getColorPiece();
    std::cout << piecePair.first << "piece5 testing line..." << piecePair.second << std::endl;
}

int main(int argc, const char *argv[])
{
    //checkForNontypeTemplate();
    checkForTypeTemplate();

    checkForBasicFColor();
    checkForBasicBGColor();

    newCheck();
    return 0;
}
