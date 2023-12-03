//
// Created by ninte on 12/3/2023.
//

#include "../include/pixelClass.h"

Pixel::Pixel(int red, int green, int blue, int alpha) {
    this->redValue = red;
    this->greenValue = green;
    this->blueValue = blue;
    this->alphaValue = alpha;
}

int Pixel::getRed() {
    return redValue;
}

int Pixel::getGreen() {
    return greenValue;
}

int Pixel::getBlue() {
    return blueValue;
}

int Pixel::getAlpha() {
    return alphaValue;
}

void Pixel::setRed(int red) {
    this->redValue = red;
}

void Pixel::setGreen(int green) {
    this->greenValue = green;
}

void Pixel::setBlue(int blue) {
    this->blueValue = blue;
}

void Pixel::setAlpha(int alpha) {
    this->alphaValue = alpha;
}