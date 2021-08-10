#ifndef PROJECT_DITHERINGRGB_H
#define PROJECT_DITHERINGRGB_H


#include "inc.h"
#include "dithering.h"

class DitheringRGB : private Dithering{
protected:
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

public:
    DitheringRGB();
    ~DitheringRGB();

    void dither(int type);
};

#endif //PROJECT_DITHERINGRGB_H
