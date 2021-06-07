#ifndef __NETPBM_H__
#define __NETPBM_H__

#include "../inc/inc.h"

class NetPBM {
    void commentHandler();

    protected:
    std::string magicNumber;
    int height;
    int width;
    std::string backgroundColor;
    std::vector<int> commentLines;
    std::vector<std::string>* file;

    public:

    NetPBM(std::vector<std::string>* file, std::string magicNumber,int height,int width, std::string backgroundColor);
    NetPBM(std::vector<std::string>* file);
    virtual ~NetPBM();

    std::vector<std::string> getImage();
    int ditheringMessage();

    virtual void createFile() = 0;
    virtual void validateFile() = 0;
    virtual void ditherImage()  = 0;
    virtual void cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) = 0;
    virtual void resizeImage() = 0;
};

class Pbm : public NetPBM {
    Pbm(std::vector<std::string>* file, std::string magicNumber,int height,int width, std::string backgroundColor);
    Pbm(std::vector<std::string>* file);
    void createFile();
    void validateFile();
    void ditherImage();
    void cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY);
    void resizeImage();
};

class Pgm : public NetPBM {
    Pgm(std::vector<std::string>* file, std::string magicNumber,int height,int width, std::string backgroundColor);
    Pgm(std::vector<std::string>* file);
    void createFile();
    void validateFile();
    void ditherImage();
    void cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY);
    void resizeImage();
};

class Ppm : public NetPBM {
    Ppm(std::vector<std::string>* file, std::string magicNumber,int height,int width, std::string backgroundColor);
    Ppm(std::vector<std::string>* file);
    void createFile();
    void validateFile();
    void ditherImage();
    void cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY);
    void resizeImage();
};

#endif