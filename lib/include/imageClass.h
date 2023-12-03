//
// Created by ninte on 12/3/2023.
//
#include <iostream>


#ifndef SPOTTHEDIFFERENCE_IMAGECLASS_H
#define SPOTTHEDIFFERENCE_IMAGECLASS_H

#include "pixelClass.h"
#include "../cimg/CImg.h"
using namespace cimg_library;

class Image {
private:
    CImg<unsigned char> data;
    int x{},y{},n{};
    int size = 0;
    const char* inputFileName{}; //hi.png
    const char* outputFileName{}; //save final tempFileName hialltransforms.png
    //make an array of pixels
    Pixel** pixelArray{}; //make dynamic array

//    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
    Pixel **copyPixelArray(Pixel** source, int numRows, int numCols);

    Pixel **makeTempArray(Pixel** tempArray,int numRows, int numCols);


public:

    explicit Image(const char* filename);
    Image(int x, int y, int n);
    Image(const Image& img);
    ~Image();

    void makePixelArray();

    void fillPixelArray();

    unsigned char* convert2Dto1D(Pixel** pixelArray);

    bool read (const char* filename);

    void flipImageVertically();
    void flipImageHorizontally();
    void rotate90Right();
    void rotate90Left();
    void makeBorder(int thickness, Pixel borderColor);
    Pixel addBorderPixel(Pixel pixel, Pixel borderColor);
    void createPointillism();
    int makeMinRadius(int x, int y);
    int makeMaxRadius(int x, int y);

    void deconstructArray(Pixel** array);

    void write (const char* filename);
};


#endif //SPOTTHEDIFFERENCE_IMAGECLASS_H
