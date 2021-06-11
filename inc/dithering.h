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
    Dithering(int height, int width, int man, std::vector<int> imageGrid);
    ~Dithering() = default;
    void dither(int type);
    std::vector<std::vector<int>> returnImage();
};

#endif