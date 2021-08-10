#ifndef PROJECT_IMAGE_H
#define PROJECT_IMAGE_H

#include "inc.h"

class Image {

    Image();
    int width;
    int height;
    int max;
    int type;
    std::vector <int> pixels;

public:
    static Image& getInstance();
    Image(Image const&) = delete;
    void operator=(Image const&) = delete;

    int getWidth();
    int getHeight();
    int getMax();
    int getType();
    std::vector <int> getPixels();

    void setWidth(int width);
    void setHeight(int height);
    void setMax(int max);
    void setPixels(std::vector<int> pixels);
    void setType(int type);

    void clear();
    void clearPixels();
};


#endif
