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
    printf("Color test: %s",
            colorStr("Green forecolor & Red backgroundcolor",
                color::ForeColor::GREEN,
                color::BackgroundColor::RED_BACK).c_str());

    // Correct: Used the removed move function
    //ColorStr<0> otherColorStr = std::move(colorStr);
    //printf("Color test: %s\n",
            //otherColorStr("Green forecolor & Red backgroundcolor",
                //color::ForeColor::GREEN,
                //color::BackgroundColor::RED_BACK).c_str());

    P("Done");
}

// FIXME：Sticky Output
void checkForTypeTemplate() {
    P("Normal template ColorStr<size_t> testing...");

    ColorStr<40> colorStr("ColorString \nmultiline \ntseting...", color::ForeColor::BLUE, color::BackgroundColor::YELLOW_BACK);
    std::cout << colorStr.originalString() << std::endl;
    std::cout << colorStr << std::endl;


    ColorStr<40> moveStr(std::move(colorStr));  // move construction
    //ColorStr<39> moveStr(std::move(colorStr));  // move construction: error
    std::cout << moveStr << std::endl;

    std::cout << moveStr.toColoredString(color::ForeColor::YELLOW, color::BackgroundColor::GREEN_BACK) << std::endl;

    P("Done");
}

void checkForBasicFColor() {
    P("Basic foreColor display...");

    ColorStr<0> colorStr;
    for (color::ForeColor fColorIterator = static_cast<color::ForeColor>(0);
            fColorIterator < color::ForeColor::NUM_FORE_COLOR;
            fColorIterator = static_cast<color::ForeColor>(static_cast<unsigned char>(fColorIterator) + 1)) {
        printf("%s\n", colorStr("ForeColor Display...", static_cast<color::ForeColor>(fColorIterator), color::BackgroundColor::NONE).c_str());
    }

    P("Done");
}

void checkForBasicBGColor() {
    P("Basic backgroundColor display...");

    ColorStr<0> colorStr;
    for (color::BackgroundColor bGColorIterator = static_cast<color::BackgroundColor>(0);
            bGColorIterator < color::BackgroundColor::NUM_BACKGROUND_COLOR;
            bGColorIterator = static_cast<color::BackgroundColor>(static_cast<unsigned char>(bGColorIterator) + 1))
                // XXX: Will be come back and append the line cut
        printf("%s\n", colorStr("BackgroundColor Display...", color::ForeColor::NONE, static_cast<color::BackgroundColor>(bGColorIterator)).c_str());

    P("Done");
}

void checkForBasicColor() {
    P("Basic CombinationColor display...");

    ColorStr<0> colorStr;
    for (color::ForeColor fColorIterator = static_cast<color::ForeColor>(0);
            fColorIterator < color::ForeColor::NUM_FORE_COLOR;
            fColorIterator = static_cast<color::ForeColor>(static_cast<unsigned char>(fColorIterator) + 1)) {
        for (color::BackgroundColor bGColorIterator = static_cast<color::BackgroundColor>(0);
                bGColorIterator < color::BackgroundColor::NUM_BACKGROUND_COLOR;
                bGColorIterator = static_cast<color::BackgroundColor>(static_cast<unsigned char>(bGColorIterator) + 1)) {
            printf("%s ", colorStr("ColorDisplay...", static_cast<color::ForeColor>(fColorIterator), static_cast<color::BackgroundColor>(bGColorIterator)).c_str());
        }
        printf("\n\n");
    }

    P("Done");
}

// FIXME: 垃圾
void newCheck() {
    P("Original ColorPiece display...");

    // 链式build
    color::ColorPiece *piece = color::ColorPiece::New()
        ->setForeColor(color::ForeColor::BLACK)
        ->setBackgroundColor(color::BackgroundColor::WHITE_BACK)
        //->setHighLight()
        //->setUnderLine()
        ->setFlash()
        //->setReverseVideo()
        //->setBlank()
        ->build();
    // 取头尾两块颜色格式片
    std::cout << piece->head() << "piece testing line..." << piece->tail() << std::endl;
    // pointer：同一个地址
    color::ColorPiece *piece1(std::move(piece));
    std::cout << piece1->head() << "piece1 testing line..." << piece1->tail() << std::endl;

    std::pair<const char*, const char*> piece_trait = piece1->getColorPiece();
    delete piece1;

    std::cout << piece_trait.first << "piece trait testing line..." << piece_trait.second << std::endl;
    // FIXME: ERROR: move construction by pointer
    //color::ColorPiece piece2(std::move(*piece1));

    color::ColorPiece piece3;
    piece3.setForeColor(color::ForeColor::BLUE);
    piece3.setBackgroundColor(color::BackgroundColor::YELLOW_BACK);
    piece3.setFlash();
    piece3.build();
    std::cout << piece3.head() << "piece3 testing line..." << piece3.tail() << std::endl;

    // move construction
    color::ColorPiece piece4(std::move(piece3));
    piece4.reset(color::ForeColor::BLUE, color::BackgroundColor::BLUE_BACK);
    piece4.setFlash(false);
    piece4.condBuild();
    std::cout << piece4.head() << "piece4 testing line..." << piece4.tail() << std::endl;
    // move assigement
    color::ColorPiece piece5 = std::move(piece4);
    piece5.resetAll();
    piece5.setFlash(true);
    piece5.condBuild();
    std::pair<const char*, const char*> piecePair = piece5.getColorPiece();
    std::cout << piecePair.first << "piece5 testing line..." << piecePair.second << std::endl;

    P("Done");
}

void checkForColorOstream() {
    P("ColorStr Output by ostream");

    ColorStr<40> colorStr("ColorString multiline\n ostream output", color::ForeColor::BLUE, color::BackgroundColor::YELLOW_BACK);
    std::cout << colorStr << std::endl;

    P("Done");
}

int main(int argc, const char *argv[])
{
    //checkForNontypeTemplate();
    checkForTypeTemplate();

    checkForBasicFColor();
    checkForBasicBGColor();
    checkForBasicColor();

    newCheck();

    checkForColorOstream();
    return 0;
}
