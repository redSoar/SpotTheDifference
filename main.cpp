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

int main() {
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
}