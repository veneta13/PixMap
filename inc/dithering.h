#ifndef DITHERING_
#define DITHERING_

#include "inc.h"
#include "image.h"


/**
 * @class Dithering
 * @brief Base class of DitheringGrayscale and DitheringRGB.
 *
 * Used to implement the dithering algorithms.
 */
class Dithering {

protected:

    /**
     *  the height of the image
     */
    int height;

    /**
     *  the width of the image
     */
    int width;

    /**
     *  the max value of the image
     */
    int max;

    /**
     *  a copy of the image in matrix format
     */
    std::vector<std::vector<int>> newImage;

    virtual void floydSteinberg() = 0;

    virtual void falseFloydSteinberg() = 0;

    virtual void jarvisJudiceNinke() = 0;

    virtual void stucki() = 0;

    virtual void atkinson() = 0;

    virtual void burkes() = 0;

    virtual void sierra() = 0;

    virtual void sierraLite() = 0;

    virtual void twoRowSierra() = 0;

    virtual void ordered4x4BayerMatrix() = 0;

    virtual void ordered8x8BayerMatrix() = 0;

    void newImageToImage();

public:

    Dithering();
    virtual ~Dithering();

    virtual void dither(int type) = 0;
};

#endif