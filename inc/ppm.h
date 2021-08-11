#ifndef PPM_
#define PPM_

#include "netpbm.h"

/**
 * @class PPM
 * @brief Handles image manipulation for PPM files.
 */
class Ppm : public NetPBM {

    public:

    Ppm();

    ~Ppm();

    void createFile(std::string bgcolor) override;

    void validateFile() override;

    void ditherImage() override;

    void cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) override;

    void resizeImage(int percentage) override;

    void resizeImage(int width, int height) override;
};


#endif
