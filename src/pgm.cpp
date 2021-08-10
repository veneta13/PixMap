#include "../inc/pgm.h"

Pgm::Pgm() {}

Pgm::~Pgm() {}

void Pgm::createFile(std::string bgcolor) {

    Image& image = Image::getInstance();
    std::vector<int> imageGrid;

    //ensure the hexadecimal color is grayscale
    if (bgcolor.at(1) != bgcolor.at(3) ||
        bgcolor.at(3) != bgcolor.at(5) ||
        bgcolor.at(1) != bgcolor.at(5) ||
        bgcolor.at(2) != bgcolor.at(4) ||
        bgcolor.at(4) != bgcolor.at(6) ||
        bgcolor.at(2) != bgcolor.at(6))
    {
        throw std::invalid_argument("Error: The hexadecimal background color is not grayscale.");
    }

    //create pixel
    int pixel = 0;

    for (int j = 1; j < 3; j++)
    {
        //convert color to integer
        char c = bgcolor.at(j);
        int temp = hexToInt(c);

        if (j % 2 == 0) { pixel += temp; }
        else            { pixel = (16 * temp); }
    }

    for (int i = 0; i < image.getHeight() * image.getWidth(); i++)
    {
        imageGrid.push_back(pixel);
    }

    image.setPixels(imageGrid);

}

void Pgm::validateFile() {

    //check if file is valid PGM file

    Image& image = Image::getInstance();

    if (image.getHeight() < 1 || image.getWidth() < 1) {
        throw std::runtime_error("Error: Invalid height or width.");
    }

    if (image.getMax() > 65535) {
        throw std::runtime_error("Error: Maximum value is 65535.");
    }

    if ((image.getPixels().size() + 1) != image.getHeight() * image.getWidth()) {
        throw std::runtime_error("Error: Height and width are inaccurate for the pixels.");
    }

    for (int i = 0; i < image.getPixels().size(); i++)
    {
        if (image.getPixels().at(i) > image.getMax()) {
            throw std::invalid_argument("Error: The value of the pixels is greater than the maximum.");
        }
    }
}

void Pgm::ditherImage() {
    //create a Dithering object
    DitheringGrayscale dithering;

    int temp = ditheringMessage();
    //dither using the object

    dithering.dither(temp);
}

void Pgm::cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {

    Image& image = Image::getInstance();

    //validate crop parameters
    validateCrop(topLeftX, topLeftY, bottomRightX, bottomRightY);

    std::vector <std::vector<int>> croppedImage;
    std::vector<int> line;

    for (int i = 0; i < image.getHeight(); i++)
    {
        for (int j = 0; j < image.getWidth(); j++)
        {
            line.push_back(image.getPixels().at(i * width + j));
        }
        croppedImage.push_back(line);
        line.clear();
    }

    image.clearPixels();
    std::vector<int> imageGrid;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i < topLeftY && i > bottomRightY && j > topLeftX && j < bottomRightX) {
                imageGrid.push_back(croppedImage.at(i).at(j));
            }
        }
    }

    image.setPixels(imageGrid);
    imageGrid.clear();
    croppedImage.clear();
}

void Pgm::resizeImage(int percentage) {

    Image& image = Image::getInstance();

    //update width and height to match the percentage
    int newWidth = (image.getWidth() * percentage) / 100;
    int newHeight = (image.getHeight() * percentage) / 100;

    //resize image
    resizeImage(newWidth, newHeight);
}

void Pgm::resizeImage(int width, int height) {

    Image& image = Image::getInstance();

    //save result into scaledImage
    std::vector<int> scaledImage;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //scale
            int srcX = int(round(float(x) / float(width) * float(this->width)));
            int srcY = int(round(float(y) / float(width) * float(this->height)));
            srcX = std::min(srcX, this->width - 1);
            srcY = std::min(srcY, this->height - 1);
            scaledImage.push_back(image.getPixels().at(this->width * srcY + srcX));
        }
    }

    //save result into ImageGrid
    image.clearPixels();
    image.setPixels(scaledImage);
    scaledImage.clear();

    //update width and height
    image.setWidth(width);
    image.setHeight(height);
}