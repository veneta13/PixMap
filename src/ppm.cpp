#include "../inc/ppm.h"

Ppm::Ppm() {}

Ppm::~Ppm() {}

void Ppm::createFile(std::string bgcolor) {

    Image image = Image::getInstance();
    std::vector<int> imageGrid;

    int rgb[3]; //rgb triple
    int pixel = 0;
    int temp = 0;

    //individual colors
    for (int i = 1; i < 7; i++)
    {
        char c = bgcolor.at(i);
        temp = hexToInt(c);

        if (i % 2 == 0) {
            pixel += temp;
            rgb[(i / 2) - 1] = pixel;
        }
        else {
            pixel = (16 * temp);
        }
    }

    //save  pixels
    for (int i = 0; i < height * width * 3; i++) {
        if (i % 2 == 0) {
            imageGrid.push_back(rgb[0]);
        } else if (i % 2 == 1) {
            imageGrid.push_back(rgb[1]);
        } else {
            imageGrid.push_back(rgb[2]);
        }
    }

    image.setPixels(imageGrid);

}

void Ppm::validateFile() {

    //check if file is valid PPM file

    Image image = Image::getInstance();

    if (image.getHeight() < 1 || image.getWidth() < 1) {
        throw std::runtime_error("Error: Invalid height or width.");
    }

    if ( ((image.getPixels().size() + 1) * 3) != (image.getHeight() * image.getWidth()) ) {
        throw std::runtime_error("Error: Height and width are inaccurate for the pixels.");
    }

    if (image.getMax() > 65535) {
        throw std::runtime_error("Error: Maximum value is 65535.");
    }

    for (int i = 0; i < image.getPixels().size(); i++)
    {
        if (image.getPixels().at(i) > image.getMax()) {
            throw std::invalid_argument("The value of the pixels is greater than the maximum.");
        }
    }
}

void Ppm::ditherImage() {
    //create a Dithering object
    DitheringRGB dithering;

    int temp = ditheringMessage();
    //dither using the object

    dithering.dither(temp);
}

void Ppm::cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {

    Image image = Image::getInstance();

    //validate crop parameters
    validateCrop(topLeftX, topLeftY, bottomRightX, bottomRightY);

    //save result to croppedImage
    std::vector <std::vector<int>> croppedImage;
    std::vector<int> line;

    //save imageGrid to croppedImage
    for (int i = 0; i < image.getHeight(); i++)
    {
        for (int j = 0; j < image.getWidth() * 3; j += 3)
        {
            for (int z = 0; z < 3; z++)
            {
                line.push_back(image.getPixels().at(i * width * 3 + j + z));
            }
        }

        croppedImage.push_back(line);
        line.clear();
    }

    image.clearPixels();
    std::vector<int> imageGrid;

    //save cropped part to imageGrid
    for (int i = 0; i < image.getHeight(); i++)
    {
        for (int j = 0; j < image.getWidth() * 3; j += 3)
        {
            if (i < topLeftY && i > bottomRightY && j > topLeftX * 3 && j < bottomRightX * 3) {
                imageGrid.push_back(croppedImage.at(i).at(j));
                imageGrid.push_back(croppedImage.at(i).at(j + 1));
                imageGrid.push_back(croppedImage.at(i).at(j + 2));
            }
        }
    }

    image.setPixels(imageGrid);
    imageGrid.clear();
    croppedImage.clear();
}

void Ppm::resizeImage(int percentage) {

    Image image = Image::getInstance();

    //update width and height to match the percentage
    int newWidth = (image.getWidth() * percentage) / 100;
    int newHeight = (image.getHeight() * percentage) / 100;

    //resize image
    resizeImage(newWidth, newHeight);
}

void Ppm::resizeImage(int width, int height) {

    Image image = Image::getInstance();

    //save scaledImage into scaledImage
    std::vector<int> scaledImage;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width * 3; x++) {
            //scale
            int srcX = int(round(float(x) / float(width * 3) * float(this->width * 3)));
            int srcY = int(round(float(y) / float(width * 3) * float(this->height * 3)));
            srcX = std::min(srcX, (this->width) * 3 - 4);
            srcY = std::min(srcY, (this->height) * 3 - 4);
            //save new image
            scaledImage.push_back(image.getPixels().at(this->width * srcY + srcX));
        }
    }

    imageGrid.clear();
    //save scaledImage into imageGrid
    imageGrid = scaledImage;
    scaledImage.clear();

    //update width and height
    image.setWidth(newWidth);
    image.setHeight(newHeight);
}