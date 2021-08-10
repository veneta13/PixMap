#ifndef PROJECT_IMAGE_H
#define PROJECT_IMAGE_H

#include "inc.h"

class Image {

    Image();
    int width;
    int height;
    int max;
    std::vector <int> pixels;

public:
    static Image& getInstance();
    Image(Image const&) = delete;
    void operator=(Image const&) = delete;

    int getWidth();
    int getHeight();
    int getMax();
    std::vector <int> getPixels();

    void setWidth(int width);
    void setHeight(int height);
    void setMax(int max);
    void setPixels(std::vector<int> pixels);

    void clear();
    void clearPixels();
};


#endif
