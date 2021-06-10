#ifndef __NETPBM_H__
#define __NETPBM_H__

#include "inc.h"
#include "dithering.h"

class NetPBM {

    protected:
    int height;
    int width;
    int max;
    std::vector<int> imageGrid;

    int hexToInt (char hex);
    int ditheringMessage();
    void validateCrop(int topLeftX, int topLeftY, int& bottomRightX, int& bottomRightY);
    
    public:

    NetPBM ();
    virtual ~NetPBM();

    virtual void createFile(std::string bgcolor) = 0;
    virtual void validateFile() = 0;
    virtual void ditherImage() = 0;
    virtual void cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) = 0;
    virtual void resizeImage(int number, bool isPercentage) = 0;
};

class Pbm : public NetPBM {
    public:
    Pbm(int height, int width, std::vector<int>& imageGrid);
    ~Pbm();
    void createFile(std::string bgcolor) override;
    void validateFile() override;
    void ditherImage() override;
    void cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) override;
    void resizeImage(int number, bool isPercentage) override;
};

class Pgm : public NetPBM {
    public:
    Pgm (int height, int width, int max, std::vector<int>& imageGrid);
    ~Pgm(); 
    void createFile(std::string bgcolor) override;
    void validateFile() override;
    void ditherImage() override;
    void cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) override;
    void resizeImage(int number, bool isPercentage) override;
};

class Ppm : public NetPBM {
    public:
    Ppm (int height, int width, int max, std::vector <int>& imageGrid);
    ~Ppm(); 
    void createFile(std::string bgcolor) override;
    void validateFile() override;
    void ditherImage() override;
    void cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) override;
    void resizeImage(int number, bool isPercentage) override;
};

#endif