//
// Created by ninte on 11/30/2023.
//
#include <iostream>
#include <vector>
#include <random>
#include "lib/include/imageClass.h"
using namespace std;

void randomEffectToOccur(Image& sectionImage, mt19937& randomNumberGenerator);
//pa03 stuff added
int main() {
    std::random_device rd;
    std::mt19937 randomNumberGenerator(rd());
    Image test("../5starPlate-up.png");
    vector<Image> sampleSections;
    for (int i = 0; i < 9; i++) {
        Image sampleImage("../5starPlate-up.png");
        int startX = sampleImage.getXSectionSize(3) * (i % 3);
        int startY = sampleImage.getYSectionSize(3) * (i / 3);
        sampleImage.resizeImage(sampleImage.getXSectionSize(3), sampleImage.getYSectionSize(3), startX, startY);
        sampleSections.push_back(sampleImage);
    }
    std::uniform_int_distribution<> section(0, 8);
    int sectionNumber = section(randomNumberGenerator);
    randomEffectToOccur(sampleSections[sectionNumber], randomNumberGenerator);
    test.makePixelArray();
    test.fillPixelArray();
    test.combine(test, sampleSections);
    test.write("../test.png");
}

void randomEffectToOccur(Image& sectionImage, mt19937& randomNumberGenerator) {
    std::uniform_int_distribution<> effect(0, 4);
    int editType = effect(randomNumberGenerator);
    if (editType == 0) {
        sectionImage.flipImageVertically();
    }
    else if (editType == 1) {
        sectionImage.flipImageHorizontally();
    }
    else if (editType == 2) {
        sectionImage.changeColorValue(randomNumberGenerator);
    }
    else if (editType == 3) {
        std::uniform_int_distribution<> thicknessValue(0, 100);
        std::uniform_int_distribution<> colorValue(0, 255);
        int thickness = thicknessValue(randomNumberGenerator);
        int redValue = colorValue(randomNumberGenerator);
        int greenValue = colorValue(randomNumberGenerator);
        int blueValue = colorValue(randomNumberGenerator);
        Pixel borderPixel;
        borderPixel.setRed(redValue);
        borderPixel.setGreen(greenValue);
        borderPixel.setBlue(blueValue);
        sectionImage.makeBorder(thickness, borderPixel);
    }
    else {
        sectionImage.createPointillism();
    }
}