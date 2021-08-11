#include "../inc/dithering.h"

Dithering::Dithering() {}

Dithering::~Dithering() {}

void Dithering::newImageToImage()
{
    //save the newImage information
    //into the Image instance
    Image& image = Image::getInstance();

    std::vector<int> imageGrid;

    for (int i = 0; i < newImage.size(); i++)
    {
        for (int j = 0; j < newImage.at(i).size(); j++)
        {
            imageGrid.push_back(newImage.at(i).at(j));
        }
    }

    image.setPixels(imageGrid);
}
