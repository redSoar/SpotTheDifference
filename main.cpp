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