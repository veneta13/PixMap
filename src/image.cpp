#include "../inc/image.h"

 Image::Image() {}

 ///
 /// @return the instance of the Image class
 Image& Image::getInstance()
{
    static Image instance;
    return instance;
}

///
/// @return image width
int Image::getWidth()
{
    return width;
}

///
/// @return image height
int Image::getHeight()
{
    return height;
}

///
/// @return image max
int Image::getMax()
{
    return max;
}

///
/// @return the magic number of the image
int Image::getType()
{
    return type;
}

///
/// @return the image pixel values
std::vector <int> Image::getPixels()
{
    return pixels;
}

///
/// @param width - image width
void Image::setWidth(int width)
{
    this->width = width;
}

///
/// @param height - image height
void Image::setHeight(int height)
{
    this->height = height;
}

///
/// @param max - image max value
void Image::setMax(int max)
{
    this->max = max;
}

///
/// @param type - image magic number
void Image::setType(int type)
{
    this->type = type;
}

///
/// @param pixels - the image pixel values
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