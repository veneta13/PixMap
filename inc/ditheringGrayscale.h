#ifndef DITHERINGGRAYSCALE_
#define DITHERINGGRAYSCALE_

#include "inc.h"
#include "dithering.h"

/**
 * @class DitheringGrayscale
 * @brief Handles dithering for PBM and PGM files.
 *
 * Derived class of Dithering.
 */
class DitheringGrayscale : public Dithering{
private:
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
    DitheringGrayscale();
    ~DitheringGrayscale();

    void dither(int type);
};

#endif
