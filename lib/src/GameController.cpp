//
// Created by Hyper on 12/5/2023.
//

#include <iostream>
#include <random>
#include "../include/imageClass.h"
#include "../include/GameController.h"

GameController::GameController(vector<string> &newList) {
    listOfImages = newList;
    currentStage = GameStage::MainMenu;
}

void GameController::randomEffectToOccur(Image& sectionImage, mt19937& randomNumberGenerator) {
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
        std::uniform_int_distribution<> thicknessValue(1, 5);
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

pair<int, int> GameController::processImage(const string& fileName) {
    random_device rd;
    mt19937 randomNumberGenerator(rd());

    Image test(fileName.c_str());
    vector<Image> sampleSections;
    for (int i = 0; i < 9; i++) {
        Image sampleImage(fileName.c_str());
        int startX = sampleImage.getXSectionSize(3) * (i % 3);
        int startY = sampleImage.getYSectionSize(3) * (i / 3);
        sampleImage.resizeImage(sampleImage.getXSectionSize(3), sampleImage.getYSectionSize(3), startX, startY);
        sampleSections.push_back(sampleImage);
    }
    std::uniform_int_distribution<> section(0, 8);
    int sectionNumber = section(randomNumberGenerator);
    int startX = test.getXSectionSize(3) * (sectionNumber % 3);
    int startY = test.getYSectionSize(3) * (sectionNumber / 3);
    int xSize = test.getXSectionSize(3);
    int ySize = test.getYSectionSize(3);

    imageButton = {startX, startY, xSize, ySize};
    randomEffectToOccur(sampleSections[sectionNumber], randomNumberGenerator);
    test.makePixelArray();
    test.fillPixelArray();
    test.combine(test, sampleSections);
    test.write("../imageChanged/currentImage.bmp");
    pair<int, int> newDimensions {test.getXSectionSize(1), test.getYSectionSize(1)};
    return newDimensions;
}

bool GameController::isButtonClicked(SDL_Event &curEvent, SDL_Rect &curButton) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    return x >= curButton.x && x < curButton.x + curButton.w &&
           y >= curButton.y && y < curButton.y + curButton.h &&
           curEvent.type == SDL_MOUSEBUTTONDOWN && curEvent.button.button == SDL_BUTTON_LEFT;
}

void GameController::process(int flag) {
    if (flag == 0) {
        width = 800;
        height = 600;

        window = SDL_CreateWindow("Spot the Difference",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  width, height, SDL_WINDOW_ALLOW_HIGHDPI);
        if (window == nullptr) {
            std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
        }

        buttonRect = {350, 250, 100, 100};
    } else if (flag == -1) {
        SDL_DestroyTexture(imageTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        width = 800;
        height = 600;

        window = SDL_CreateWindow("Spot the Difference",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  width, height, SDL_WINDOW_ALLOW_HIGHDPI);
        if (window == nullptr) {
            std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
        }
    } else {
        SDL_DestroyTexture(imageTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        std::random_device rd;
        std::mt19937 ranNumGen(rd());
        std::uniform_int_distribution<> imageRange(0, (int) listOfImages.size() - 1);

        int newWidth {};
        int newHeight {};

        while(true) {
            bool isCopyFound = false;
            int img = imageRange(ranNumGen);
            string curImage = listOfImages[img];
            for (int i = 0; i < usedImages.size(); i++) {
                if (curImage == usedImages[i]) {
                    isCopyFound = true;
                }
            }
            if (!isCopyFound) {
                pair<int, int> newCoords = processImage(curImage);
                newWidth = newCoords.first;
                newHeight = newCoords.second;
                imageSurface = SDL_LoadBMP("../imageChanged/currentImage.bmp");
                if (imageSurface == nullptr) {
                    std::cout << "SDL could not load image: " << SDL_GetError() << std::endl;
                }
                usedImages.push_back(curImage);
                break;
            }
        }

        window = SDL_CreateWindow("Spot the Difference",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  newWidth, newHeight, SDL_WINDOW_ALLOW_HIGHDPI);
        if (window == nullptr) {
            std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
        }

        imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        SDL_FreeSurface(imageSurface);

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    }
}

void GameController::run() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
    }

    while (true) {
        if (SDL_PollEvent(&event)) {
            if (SDL_QUIT == event.type) {
                break;
            }

            if (SDL_MOUSEBUTTONDOWN == event.type) {
                if (currentStage == GameStage::MainMenu && isButtonClicked(event, buttonRect)) {
                    process(1);
                    currentStage = GameStage::Stage1;
//                    currentStage = GameStage::Instructions;
                } else if (currentStage == GameStage::Instructions && isButtonClicked(event, buttonRect)) {
                    process(1);
                    currentStage = GameStage::Stage1;
                } else if (currentStage == GameStage::Stage1) {
                    if (isButtonClicked(event, imageButton)) {
                        process(2);
                        currentStage = GameStage::Stage2;
                    } else {
                        process(-1);
                        currentStage = GameStage::LoseScreen;
                    }
                } else if (currentStage == GameStage::Stage2) {
                    if (isButtonClicked(event, imageButton)) {
                        process(3);
                        currentStage = GameStage::Stage3;
                    } else {
                        process(-1);
                        currentStage = GameStage::LoseScreen;
                    }
                } else if (currentStage == GameStage::Stage3) {
                    if (isButtonClicked(event, imageButton)) {
                        process(-1);
                        currentStage = GameStage::WinScreen;
                    } else {
                        process(-1);
                        currentStage = GameStage::LoseScreen;
                    }
                }
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw the button
        if (currentStage == GameStage::MainMenu) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 150, 255);
            SDL_RenderFillRect(renderer, &buttonRect);
        } else if (currentStage == GameStage::Instructions) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 150, 255);
            SDL_RenderFillRect(renderer, &buttonRect);
        } else if (currentStage == GameStage::Stage1) {
            SDL_RenderCopy(renderer, imageTexture, nullptr, nullptr);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderFillRect(renderer, &imageButton);
        } else if (currentStage == GameStage::Stage2) {
            SDL_RenderCopy(renderer, imageTexture, nullptr, nullptr);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderFillRect(renderer, &imageButton);
        } else if (currentStage == GameStage::Stage3) {
            SDL_RenderCopy(renderer, imageTexture, nullptr, nullptr);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderFillRect(renderer, &imageButton);
        } else if (currentStage == GameStage::LoseScreen) {
            SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
            SDL_RenderFillRect(renderer, &buttonRect);
        } else if (currentStage == GameStage::WinScreen) {
            SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
            SDL_RenderFillRect(renderer, &buttonRect);
        }

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(imageTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
