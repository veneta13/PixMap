#include "../inc/pbm.h"

Pbm::Pbm() {}

Pbm::~Pbm() {}

void Pbm::createFile(std::string bgcolor) {
    //create file according to bgcolor
    int pixel;

    if (bgcolor == "#FFFFFF") {
        pixel = 0;
    } else if (bgcolor == "#000000") {
        pixel = 1;
    } else {
        throw std::invalid_argument("Invalid background color for PBM.");
    }

    std::vector <int> imageGrid;

    for (int i = 0; i < height * width; i++) {
        imageGrid.push_back(pixel);
    }

    Image& image = Image::getInstance();
    image.setPixels(imageGrid);
}

void Pbm::validateFile() {

    //check if the file is valid PBM file

    Image& image = Image::getInstance();

    if (image.getHeight() < 1 || image.getWidth() < 1) {
        throw std::runtime_error("Error: Invalid height or width.");
    }

    if ( (image.getPixels().size() + 1) != (image.getHeight() * image.getWidth()) ) {
        throw std::runtime_error("Error: Height and width are inaccurate for the pixels.");
    }

    for (int i = 0; i < image.getPixels().size(); i++)
    {
        if ((image.getPixels().at(i) != 0)
        ||  (image.getPixels().at(i) != 1))
        {
            throw std::runtime_error("Error: File does not contain only 1 and 0.");
        }
    }
}

void Pbm::ditherImage() {
    //create a Dithering object
    DitheringGrayscale dithering;

    int temp = ditheringMessage();
    //dither using the object

    dithering.dither(temp);
}

void Pbm::cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {

    Image& image = Image::getInstance();

    //validate crop parameters
    validateCrop(topLeftX, topLeftY, bottomRightX, bottomRightY);

    //save imageGrid to croppedImage
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

void Pbm::resizeImage(int percentage) {

    Image& image = Image::getInstance();

    //update width and height to match the percentage
    int newWidth = (image.getWidth() * percentage) / 100;
    int newHeight = (image.getHeight() * percentage) / 100;

    //resize image
    resizeImage(newWidth, newHeight);
}

void Pbm::resizeImage(int width, int height) {

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

    //save scaled image to imageGrid
    imageGrid.clear();
    imageGrid = scaledImage;
    scaledImage.clear();

    //update width and height
    image.setWidth(width);
    image.setHeight(height);
}