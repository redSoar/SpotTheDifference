//
// Created by ninte on 12/3/2023.
//

#ifndef SPOTTHEDIFFERENCE_PIXELCLASS_H
#define SPOTTHEDIFFERENCE_PIXELCLASS_H


class Pixel {
private:
    int redValue{};
    int greenValue{};
    int blueValue{};
    int alphaValue{};

public:

    Pixel() = default;
    explicit Pixel(int red, int green, int blue, int alpha);

    int getRed();
    int getGreen();
    int getBlue();
    int getAlpha();

    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);
    void setAlpha(int alpha);
};


#endif //SPOTTHEDIFFERENCE_PIXELCLASS_H
