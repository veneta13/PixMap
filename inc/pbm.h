#ifndef PBMH
#define PBMH

#include "netpbm.h"

class Pbm : public NetPBM {

    public:

    Pbm();

    ~Pbm();

    void createFile(std::string bgcolor) override;

    void validateFile() override;

    void ditherImage() override;

    void cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) override;

    void resizeImage(int percentage) override;

    void resizeImage(int width, int height) override;
};

#endif
