#ifndef PGM_
#define PGM_

#include "netpbm.h"

/**
 * @class PGM
 * @brief Handles image manipulation for PGM files.
 */
class Pgm : public NetPBM {

    public:

    Pgm();

    ~Pgm();

    void createFile(std::string bgcolor) override;

    void validateFile() override;

    void ditherImage() override;

    void cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) override;

    void resizeImage(int percentage) override;

    void resizeImage(int width, int height) override;
};


#endif
