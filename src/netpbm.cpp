#include "../inc/netpbm.h"

NetPBM::NetPBM(std::vector<std::string>* file, std::string magicNumber,int height,int width, std::string backgroundColor)
    : file(file), 
      magicNumber(magicNumber), 
      height(height), 
      width(width), 
      backgroundColor(backgroundColor)
{
    std::string size;
    size = std::to_string(height) + " " + std::to_string(width);
    (*file).push_back(magicNumber);
    (*file).push_back(size);
}

NetPBM::NetPBM(std::vector<std::string>* file)
{
    this->file = file;
    commentHandler();
}

std::vector<std::string> NetPBM::getImage()
{
    return (*file);
}

void NetPBM::commentHandler()
{
    for (int i = 0; i < (*file).size(); i++)
    {
        if ( (*file)[i].find("#") != std::string::npos){
            commentLines.push_back(i);
        }
    }
}

void Pbm::createFile()
{
    if (backgroundColor == "#FFFFFF" || backgroundColor == "#000000"){
        int bgPixel = (backgroundColor == "#000000") ? 1 : 0;
        std::string line = "";

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                line += std::to_string(bgPixel);
            }
            (*file).push_back(line);
        }
    }
    else {
        throw std::invalid_argument("Error: This background color is invalid for a PBM image.");
    }
}

void Pbm::validateFile()
{

}

void Pbm::ditherImage()
{

}

void Pbm::cropImage()
{

}

void Pbm::resizeImage()
{

}

void Pgm::createFile()
{

}

void Pgm::validateFile()
{

}

void Pgm::ditherImage()
{

}

void Pgm::cropImage()
{

}

void Pgm::resizeImage()
{

}

void Ppm::createFile()
{

}

void Ppm::validateFile()
{

}

void Ppm::ditherImage()
{

}

void Ppm::cropImage()
{

}

void Ppm::resizeImage()
{

}