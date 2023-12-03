//
// Created by ninte on 12/3/2023.
//

#include "../include/imageClass.h"

using namespace std;

Image::Image(const char* filename) {
    if(read(filename)) {
        //works
        std::cout << "I'm reading: " << inputFileName << std::endl;
        size = x * y * n;
        this->pixelArray = nullptr;
    }
    else {
        //error
        std::cout << "Error occurred in reading file" << std::endl;
    }
}

Image::Image(int x, int y, int n) : x(x), y(y), n(n) {
    this->size = x * y * n;
    this->data = CImg<unsigned char> (x, y, 1, n);
    this->pixelArray = nullptr;
}

Image::Image(const Image &copyImage) : Image(copyImage.x, copyImage.y, copyImage.n) {
    this->size = copyImage.size;
    this->data = copyImage.data;
    this->pixelArray = copyImage.pixelArray;
}


Image::~Image() {
    //deallocate
    for (int i = 0; i < y; i++) {
        delete[] pixelArray[i];
    }
    delete[] pixelArray;
}

void Image::makePixelArray() {
    int numRows = y;
    int numCols = x;
    this->pixelArray = new Pixel* [numRows] {};
    for (int i = 0; i < numRows; i++) {
        this->pixelArray[i] = new Pixel[numCols];
    }
}

void Image::fillPixelArray() {
    for (int d = 0; d < size; d++) {
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                for (int k = 0; k < 4; k++) {
                    if (k == 0) {
                        pixelArray[i][j].setRed(data(j,i,0,0));
                        d++;
                    }
                    else if (k == 1) {
                        pixelArray[i][j].setGreen(data(j,i,0,1));
                        d++;
                    }
                    else if (k == 2) {
                        pixelArray[i][j].setBlue(data(j,i,0,2));
                        d++;
                    }
                    else {
                        if (n % 2 == 0) {
                            pixelArray[i][j].setAlpha(data(j,i,0,3));
                            d++;
                        }
                        else {
                            pixelArray[i][j].setAlpha(1);
                        }
                    }
                }
            }
        }
    }
}

bool Image::read(const char *filename) {
    data.load(filename);
    x = data.width();
    y = data.height();
    n = data.spectrum();
    this->inputFileName = filename;
    return !data.is_empty();
}

unsigned char *Image::convert2Dto1D(Pixel **pixelArray) {
    size = x * y * n;
    data = CImg<unsigned char>(x, y, 1, n);
    int dataValue = 0;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            for (int k = 0; k < 4; k++) {
                if (k == 0) {
                    data(j, i, 0, k) = pixelArray[i][j].getRed();
                    dataValue++;
                } else if (k == 1) {
                    data(j, i, 0, k) = pixelArray[i][j].getGreen();
                    dataValue++;
                } else if (k == 2) {
                    data(j, i, 0, k) = pixelArray[i][j].getBlue();
                    dataValue++;
                } else {
                    if (n % 2 == 0) {
                        data(j, i, 0, k) = pixelArray[i][j].getAlpha();
                        dataValue++;
                    } else {
                        // no alpha value so don't do stuff
                    }
                }
            }
        }
    }
    return data;
}

void Image::write(const char *filename) {
    outputFileName = filename;
    this->data = CImg<unsigned char>(convert2Dto1D(pixelArray), x, y, 1, n);
    std::cout << "I'm writing to: " << outputFileName << std::endl;
    data.save(filename);
}

void Image::flipImageVertically() {
    //make temp array and switch y values, [0][0] == [y][0]
    Pixel** tempArray;
    tempArray = makeTempArray(tempArray,y, x);
    int flipCols = y - 1;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            tempArray[i][j].setRed(pixelArray[flipCols][j].getRed());
            tempArray[i][j].setGreen(pixelArray[flipCols][j].getGreen());
            tempArray[i][j].setBlue(pixelArray[flipCols][j].getBlue());
            tempArray[i][j].setAlpha(pixelArray[flipCols][j].getAlpha());
        }
        flipCols--;
    }
    pixelArray = copyPixelArray(tempArray, y, x);
    deconstructArray(tempArray);
}

void Image::flipImageHorizontally() {
    //make temp array and switch x values, [0][0] == [0][x]
    Pixel** tempArray;
    tempArray = makeTempArray(tempArray,y, x);
    for (int i = 0; i < y; i++) {
        int flipRows = x - 1;
        for (int j = 0; j < x; j++) {
            tempArray[i][j].setRed(pixelArray[i][flipRows].getRed());
            tempArray[i][j].setGreen(pixelArray[i][flipRows].getGreen());
            tempArray[i][j].setBlue(pixelArray[i][flipRows].getBlue());
            tempArray[i][j].setAlpha(pixelArray[i][flipRows].getAlpha());
            flipRows--;
        }
    }
    pixelArray = copyPixelArray(tempArray, y, x);
    deconstructArray(tempArray);
}

void Image::rotate90Right() {
    Pixel** tempArray;
    int temp = y;
    y = x;
    x = temp;
    tempArray = makeTempArray(tempArray,y, x);
    int rotatedCols = 0;
    for (int i = 0; i < y; i++) {
        int rotatedRows = x - 1;
        for (int j = 0; j < x; j++) {
            tempArray[i][j].setRed(pixelArray[rotatedRows][rotatedCols].getRed());
            tempArray[i][j].setGreen(pixelArray[rotatedRows][rotatedCols].getGreen());
            tempArray[i][j].setBlue(pixelArray[rotatedRows][rotatedCols].getBlue());
            tempArray[i][j].setAlpha(pixelArray[rotatedRows][rotatedCols].getAlpha());
            rotatedRows--;
        }
        rotatedCols++;
    }
    pixelArray = copyPixelArray(tempArray, y, x);
    deconstructArray(tempArray);
}

void Image::rotate90Left() {
    Pixel** tempArray;
    int temp = y;
    y = x;
    x = temp;
    tempArray = makeTempArray(tempArray,y, x);
    int rotatedCols = y - 1;
    for (int i = 0; i < y; i++) {
        int rotatedRows = 0;
        for (int j = 0; j < x; j++) {
            tempArray[i][j].setRed(pixelArray[rotatedRows][rotatedCols].getRed());
            tempArray[i][j].setGreen(pixelArray[rotatedRows][rotatedCols].getGreen());
            tempArray[i][j].setBlue(pixelArray[rotatedRows][rotatedCols].getBlue());
            tempArray[i][j].setAlpha(pixelArray[rotatedRows][rotatedCols].getAlpha());
            rotatedRows++;
        }
        rotatedCols--;
    }
    pixelArray = copyPixelArray(tempArray, y, x);
    deconstructArray(tempArray);
}

void Image::makeBorder(int thickness, Pixel borderColor) {
    if (thickness < 0) {
        cout << "You gave a negative numbers so I'm just going to make it the absolute value" << endl;
        thickness *= - 1;
    }
    Pixel** tempArray;
    this->y += (thickness * 2);
    this->x += (thickness * 2);
    tempArray = makeTempArray(tempArray,y, x);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (i > thickness && i < y - thickness) {//if not in border add pixel to spot
                if (j > thickness && j < x - thickness) {//puts image within
                    tempArray[i][j].setRed(pixelArray[i - thickness][j - thickness].getRed());
                    tempArray[i][j].setGreen(pixelArray[i - thickness][j - thickness].getGreen());
                    tempArray[i][j].setBlue(pixelArray[i - thickness][j - thickness].getBlue());
                    tempArray[i][j].setAlpha(pixelArray[i - thickness][j - thickness].getAlpha());
                }
                else {
                    tempArray[i][j] = addBorderPixel(tempArray[i][j], borderColor); //makes gold border at location
                }
            }
            else {
                tempArray[i][j] = addBorderPixel(tempArray[i][j], borderColor);//makes gold border at location
            }
        }
    }
    pixelArray = copyPixelArray(tempArray, y, x);
    deconstructArray(tempArray);
}

Pixel Image::addBorderPixel(Pixel pixel, Pixel borderColor) {
    pixel.setRed(borderColor.getRed());
    pixel.setGreen(borderColor.getGreen());
    pixel.setBlue(borderColor.getBlue());
    pixel.setAlpha(255);
    return pixel;
}

//hard
void Image::createPointillism() {
    Pixel** tempArray;
    int numIterations = (x + y) * 10; // Changes number of circles for images (based on image size)
    int minRadius = makeMinRadius(x, y);
    int maxRadius = makeMaxRadius(x, y);
    tempArray = copyPixelArray(pixelArray, y, x); // Makes the temp array (to reduce size of function)
    for (int iter = 0; iter < numIterations; iter++) {
        //Randomly selects a pixel to be "pointillissed" (not an art major)
        int randX = rand() % x;
        int randY = rand() % y;
        int radius = rand() % (maxRadius - minRadius) + minRadius;//Makes a random radius size for each time of pointillism
        //Uses radius to make the circles for pointillism
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                if (randX + i >= 0 && randX + i < x && randY + j >= 0 && randY + j < y) {
                    if (i * i + j * j <= radius * radius) {
                        // Transform the color of the pixel to match the selected pixel
                        tempArray[randY + j][randX + i] = pixelArray[randY][randX];
                    }
                }
            }
        }
    }
    pixelArray = copyPixelArray(tempArray, y, x);
    deconstructArray(tempArray);;
}

// Helper function to create a copy of the pixel array in pointillism (could have done in others but was lazy)
Pixel** Image::copyPixelArray(Pixel** source, int numRows, int numCols) {
    Pixel** copy = new Pixel*[numRows];
    for (int i = 0; i < numRows; i++) {
        copy[i] = new Pixel[numCols];
        for (int j = 0; j < numCols; j++) {
            copy[i][j] = source[i][j];
        }
    }
    return copy;
}

Pixel **Image::makeTempArray(Pixel** tempArray ,int numRows, int numCols) {
    tempArray = new Pixel* [numRows] {};
    for (int i = 0; i < numRows; i++) {
        tempArray[i] = new Pixel[numCols];
    }
    return tempArray;
}

int Image::makeMinRadius(int x, int y) {
    int minRadius;
    if (x > y) {
        minRadius = 5 * (x + y) / (x); // Adjust according to image size
    }
    else {
        minRadius = 5 * (x + y) / (y); // Adjust according to image size
    }
    return minRadius;
}

int Image::makeMaxRadius(int x, int y) {
    int maxRadius;
    if (x > y) {
        maxRadius = 10 * (x + y) / (x); // Adjust according to image size
    }
    else {
        maxRadius = 10 * (x + y) / (y); // Adjust according to image size
    }
    return maxRadius;
}

void Image::deconstructArray(Pixel **array) {
    for (int i = 0; i < y; i++) {
        delete[] array[i];
    }
    delete[] array;
}
