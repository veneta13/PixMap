#ifndef PPMH
#define PPMH

#include "netpbm.h"

class Ppm : public NetPBM {

    public:

    Ppm(int height, int width, int max, std::vector<int> &imageGrid);

    ~Ppm();

    void createFile(std::string bgcolor) override;

    void validateFile() override;

    void ditherImage() override;

    void cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) override;

    void resizeImage(int percentage) override;

    void resizeImage(int width, int height) override;
};


#endif
