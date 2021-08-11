#ifndef NETPBM_
#define NETPBM_

#include "inc.h"
#include "image.h"
#include "ditheringGrayscale.h"
#include "ditheringRGB.h"

/**
 * @class NetPBM
 * @brief Base class of PBM, PGM and PPM.
 *
 * Handles image manipulation depending on the type of image.
 */
class NetPBM {

protected:
    Dithering* dithering;

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