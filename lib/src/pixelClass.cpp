//
// Created by ninte on 12/3/2023.
//

#include "../include/pixelClass.h"

// constructor
Pixel::Pixel(int red, int green, int blue, int alpha) {
    this->redValue = red;
    this->greenValue = green;
    this->blueValue = blue;
    this->alphaValue = alpha;
}

// get red value
int Pixel::getRed() {
    return redValue;
}

// get green value
int Pixel::getGreen() {
    return greenValue;
}

// get blue value
int Pixel::getBlue() {
    return blueValue;
}

// get alpha value
int Pixel::getAlpha() {
    return alphaValue;
}

// set red value
void Pixel::setRed(int red) {
    this->redValue = red;
}

// set green value
void Pixel::setGreen(int green) {
    this->greenValue = green;
}

// set blue value
void Pixel::setBlue(int blue) {
    this->blueValue = blue;
}

// set alpha value
void Pixel::setAlpha(int alpha) {
    this->alphaValue = alpha;
}