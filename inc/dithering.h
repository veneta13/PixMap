#ifndef __DITHERING_H__
#define __DITHERING_H__

#include "inc.h"
#include "netpbm.h"

template<class A>
class Dithering
{
    int height;
    int width;
    int max;
    std::vector<std::vector<int>> newImage;

    public:
    Dithering (const A &p);
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