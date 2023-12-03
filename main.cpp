//
// Created by ninte on 11/30/2023.
//
#include <iostream>
#include "lib/include/imageClass.h"

int main() {
    Image test("../5starPlate-up.png");
    test.makePixelArray();
    test.fillPixelArray();
    test.flipImageVertically();
    test.write("../test.bmp");
}