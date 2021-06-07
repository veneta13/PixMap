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

NetPBM::~NetPBM () {} 

std::vector<std::string> NetPBM::getImage()
{
    return (*file);
}

int ditheringMessage ()
{
    std::cout << "Choose a dithering algorithm:\n"
              << "1 - Floyd-Steinberg Dithering\n"
              << "2 - “False Floyd-Steinberg” Dithering\n"
              << "3 - Jarvis, Judice, and Ninke Dithering\n"
              << "4 - Stucki Dithering\n"
              << "5 - Atkinson Dithering\n"
              << "6 - Burkes Dithering\n"
              << "7 - Sierra Dithering\n"
              << "8 - Two-Row Sierra\n"
              << "9 - Sierra Lite Dithering\n"
              << "10 - Ordered dither using a 4x4 Bayer matrix\n"
              << "11 - Ordered dither using an 8x8 Bayer matrix\n";
    int choice;
    std::cin >> choice;
    if (choice < 1 && choice > 11){
        throw std::runtime_error("Error: Invalid choice of a dithering algorithm.");
    }
    return choice;
}

void NetPBM::commentHandler()
{
    for (int i = 0; i < (*file).size(); i++)
    {
        if ( (*file)[i].at(0) == '#'){
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
    int commentLinesCounter = 0;
    for (int i = 0; i < (*file).size(); i++)
    {
        if (commentLines[commentLinesCounter] == i) {
            commentLinesCounter++;
            continue;
        }
        else {
            for (int j = 0; j < (*file)[i].length(); j++)
            {
                if ((*file)[i].length() != width) {
                    throw std::invalid_argument("Error: File width is inconsistent with width parameter.");
                } 
                else {
                    if ((*file)[i][j] != '1' || (*file)[i][j] != '0') {
                    throw std::invalid_argument("Error: The file is not in proper PBM format.");
                    }
                }
            }
        }

        if ( ((*file).size() - commentLinesCounter) != (height - 1)) {
            throw std::invalid_argument("Error: File height is inconsistent with height parameter.");
        }
    }
}

void Pbm::ditherImage()
{
    
}

void Pbm::cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)
{
    if (topLeftX > width || topLeftY > height) {
        throw std::invalid_argument("Error: Image top left point is out of bounds.");
    }
    else {
        if (bottomRightX > width){
            bottomRightX = width;
        }
        if (bottomRightY > height){
            bottomRightY = height;
        }
        
        (*file).erase((*file).begin(), (*file).begin()+(topLeftY - 1));
        //(*file).erase((*file).back() - (bottomRightY - 1), (*file).back());

        for (int i = 0; i < (*file).size(); i++) 
        {
            (*file).at(i) = (*file).at(i).substr((topLeftX-1), (bottomRightX - topLeftX));
        }
    }
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

void Pgm::cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)
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

void Ppm::cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)
{

}

void Ppm::resizeImage()
{

}
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
