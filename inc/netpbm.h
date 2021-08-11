#ifndef __NETPBM_H__
#define __NETPBM_H__

#include "inc.h"
#include "image.h"
#include "ditheringGrayscale.h"
#include "ditheringRGB.h"

class NetPBM {

protected:
    int height;
    int width;
    int max;
    std::vector<int> imageGrid;

    int hexToInt(char hex);

    int ditheringMessage();

    void validateCrop(int topLeftX, int topLeftY, int &bottomRightX, int &bottomRightY);

public:

    NetPBM();
    virtual ~NetPBM();

    virtual void createFile(std::string bgcolor) = 0;
    virtual void validateFile() = 0;
    virtual void ditherImage() = 0;
    virtual void cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) = 0;
    virtual void resizeImage(int percentage) = 0;
    virtual void resizeImage(int width, int height) = 0;
};


#endif