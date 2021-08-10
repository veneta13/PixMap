#ifndef __DITHERING_H__
#define __DITHERING_H__

#include "inc.h"
#include "image.h"

class Dithering {

protected:
    int height;
    int width;
    int max;
    std::vector<int> newImage;

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

public:

    Dithering();
    virtual ~Dithering();

    virtual void dither(int type) = 0;
};

#endif