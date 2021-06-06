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

    std::vector<std::string> getImage();
    
    virtual void createFile();
    virtual void validateFile();
    virtual void ditherImage();
    virtual void cropImage();
    virtual void resizeImage();
};

class Pbm : public NetPBM {
    void createFile();
    void validateFile();
    void ditherImage();
    void cropImage();
    void resizeImage();
};

class Pgm : public NetPBM {
    void createFile();
    void validateFile();
    void ditherImage();
    void cropImage();
    void resizeImage();
};

class Ppm : public NetPBM {
    void createFile();
    void validateFile();
    void ditherImage();
    void cropImage();
    void resizeImage();
};

#endif