//
// Created by Hyper on 12/5/2023.
//

#ifndef SPOTTHEDIFFERENCE_GAMECONTROLLER_H
#define SPOTTHEDIFFERENCE_GAMECONTROLLER_H

#include <random>
#include <vector>
#include "SDL.h"
#include "GameStage.h"
using namespace std;

class GameController {
private:
    vector<string> listOfImages;
    vector<string> usedImages {};
    int width {};
    int height {};
    SDL_Window *window {};
    SDL_Renderer *renderer {};
    SDL_Rect buttonRect {};
    SDL_Rect imageButton {};
    GameStage currentStage {};
    SDL_Surface *imageSurface {};
    SDL_Texture *imageTexture {};
    SDL_Event event {};
public:
    explicit GameController(vector<string>& newList);
    void randomEffectToOccur(Image& sectionImage, mt19937& randomNumberGenerator);
    pair<int, int> processImage(const string& fileName);
    bool isButtonClicked(SDL_Event& curEvent, SDL_Rect& curButton);
    void process(int flag);
    void run();
};

#endif //SPOTTHEDIFFERENCE_GAMECONTROLLER_H
