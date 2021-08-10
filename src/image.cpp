#include "../inc/image.h"

 Image::Image() {}

 static Image& Image::getInstance()
{
    static Image instance;
    return instance;
}

int Image::getWidth()
{
    return width;
}

int Image::getHeight()
{
    return height;
}

int Image::getMax()
{
    return max;
}

std::vector <int> Image::getPixels()
{
    return pixels;
}

void Image::setWidth(int width)
{
    this->width = width;
}

void Image::setHeight(int height)
{
    this->height = height;
}

void Image::setMax(int max)
{
    this->max = max;
}

void Image::setPixels(std::vector<int> pixels)
{
    this->pixels = pixels;
}

void Image::clear()
{
    width = 0;
    height = 0;
    max = -1;
    pixels.clear();
}

void Image::clearPixels()
{
    pixels.clear();
}