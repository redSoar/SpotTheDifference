//
// Created by ninte on 11/30/2023.
//
#include <filesystem>
#include <vector>
#include <random>
#include "lib/include/imageClass.h"
#include "lib/include/GameController.h"

namespace fs = std::filesystem;
using namespace std;

/*
 * Preprocessing (main.cpp):
 *  - All images should be .bmp BEFORE running program
 *  - Create random number generator
 *  - Create list of strings with all image paths
 *  - Create controller and pass in RNG and list of paths
 *  - Call process() function
 *    - Create window, renderer, etc..
 *  - Call run() function
 * Controller (run() function):
 *  - Pick a random image, and set width and height
 *  - Run game loop
 *    - Display image and invisible button
 *    - Change screen based on user action
 *      - Wrong, change to lose screen
 *      - Right, change to next screen
 *  - Print to the console (Print class?)
 *  - Calls enum class
 */

void randomEffectToOccur(Image& sectionImage, mt19937& randomNumberGenerator);
//pa03 stuff added
int main() {

//    random_device rd;
//    mt19937 randomNumberGenerator(rd());

    vector<string> imageList {};

    fs::path imageLocation("../images");
    if (!fs::exists(imageLocation)) {
        std::cerr << "this CML path does not exist." << std::endl;
    }
    if (!fs::is_directory(imageLocation)) {
        std::cerr << "this CML path is not a directory." << std::endl;
    }

    for (const fs::directory_entry& entry: fs::directory_iterator(imageLocation)) {
        string filePath = entry.path().string();

        if (entry.is_regular_file()) {
           imageList.push_back(filePath);
        }
    }

    GameController guessController(imageList);
    guessController.process(0);
    guessController.run();

//    Image test("../5starPlate-up.png");
//    vector<Image> sampleSections;
//    for (int i = 0; i < 9; i++) {
//        Image sampleImage("../5starPlate-up.png");
//        int startX = sampleImage.getXSectionSize(3) * (i % 3);
//        int startY = sampleImage.getYSectionSize(3) * (i / 3);
//        sampleImage.resizeImage(sampleImage.getXSectionSize(3), sampleImage.getYSectionSize(3), startX, startY);
//        sampleSections.push_back(sampleImage);
//    }
//    std::uniform_int_distribution<> section(0, 8);
//    int sectionNumber = section(randomNumberGenerator);
//    randomEffectToOccur(sampleSections[sectionNumber], randomNumberGenerator);
//    test.makePixelArray();
//    test.fillPixelArray();
//    test.combine(test, sampleSections);
//    test.write("../test.png");
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