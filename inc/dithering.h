#ifndef __DITHERING_H__
#define __DITHERING_H__

#include "inc.h"
#include "netpbm.h"

class Dithering
{
    int height;
    int width;
    int max;

    public:

    Dithering(Pbm * p);
    Dithering(Pgm * p);
    Dithering(Ppm * p);
    ~Dithering() = default;

    void floydSteinberg();
    void falseFloydSteinberg();
    void jarvisJudiceNinke();
    void stucki();
    void atkinson();
    void burkes();
    void sierra();
    void sierraLite();
    void twoRowSierra();
    void ordered4x4BayerMatrix();
    void ordered8x8BayerMatrix();
};

#endif