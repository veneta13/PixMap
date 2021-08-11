#include "../inc/netpbm.h"

// NetPBM

NetPBM::NetPBM() {}

NetPBM::~NetPBM() {}

///
/// @return the type of dithering to be executed
int NetPBM::ditheringMessage() {
    //print message and return chosen algorithm
    std::cout << "Choose a dithering algorithm:\n"
              << "1 - Floyd-Steinberg Dithering\n"
              << "2 - False Floyd-Steinberg Dithering\n"
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
    if (choice < 1 && choice > 11) {
        throw std::runtime_error("Error: Invalid choice of a dithering algorithm.");
    }
    return choice;
}

///
/// @param hex - hex value
/// @return the decimal value
int NetPBM::hexToInt(char hex)
{
    //convert hex value to integer
    switch (hex) {
        case '0' : {return 0;}
        case '1' : {return 1;}
        case '2' : {return 2;}
        case '3' : {return 3;}
        case '4' : {return 4;}
        case '5' : {return 5;}
        case '6' : {return 6;}
        case '7' : {return 7;}
        case '8' : {return 8;}
        case '9' : {return 9;}
        case 'A' : {return 10;}
        case 'B' : {return 11;}
        case 'C' : {return 12;}
        case 'D' : {return 13;}
        case 'E' : {return 14;}
        case 'F' : {return 15;}
        default :
        {throw std::runtime_error("Error: Unknown background color.");}
    }
    return -1;
}

///
/// @param topLeftX - top left x coordinates
/// @param topLeftY - top left y coordinates
/// @param bottomRightX - bottom right x coordinates
/// @param bottomRightY - bottom right y coordinates
void NetPBM::validateCrop(int topLeftX, int topLeftY, int& bottomRightX, int &bottomRightY) {

    Image& image = Image::getInstance();

    //if both coordinates are out of bounds the operation is not possible
    if (topLeftX < 1 || topLeftY < 1 || bottomRightX < 1 || bottomRightY < 1) {
        throw std::invalid_argument("Error: Coordinates must be positive.");
    }

    //if the format is grayscale
    if (image.getWidth() * image.getWidth() == image.getPixels().size()) {

        if ((topLeftX > image.getWidth() && bottomRightX > image.getWidth()) ||
            (bottomRightY > image.getHeight() && topLeftY > image.getHeight())){
            throw std::runtime_error(
                    "Error: Rectangle is out of bounds. Hint: Enter top left and bottom right coordinates.");}

        if (topLeftX > bottomRightX) {
            throw std::runtime_error("Error: The X coordinate of top left is greater than bottom right.");}

        if (topLeftY > bottomRightY) {
            throw std::runtime_error("Error: The Y coordinate of top left is greater than bottom right.");}

        //if only one coordinate is out of bounds resize to bounds
        if (bottomRightX > image.getWidth()) {
            bottomRightX = image.getWidth();
        }

        if (bottomRightY > image.getHeight()) {
            bottomRightY = image.getHeight();
        }
    } else {
        if ((topLeftX > image.getWidth() * 3 && bottomRightX > image.getWidth() * 3) ||
            (bottomRightY > image.getHeight() && topLeftY > image.getHeight())) {
            throw std::runtime_error(
                    "Error: Rectangle is out of bounds. Hint: Enter top left and bottom right coordinates.");
        }

        if (topLeftX > bottomRightX) {
            throw std::runtime_error("Error: The X coordinate of top left is greater than bottom right.");
        }

        if (topLeftY > bottomRightY) {
            throw std::runtime_error("Error: The Y coordinate of top left is greater than bottom right.");
        }

        //if only one coordinate is out of bounds resize to bounds
        if (bottomRightX > image.getWidth() * 3) {
            bottomRightX = image.getWidth() * 3;
        }

        if (bottomRightY > image.getHeight()) {
            bottomRightY = image.getHeight();
        }
    }

}