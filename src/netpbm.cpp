#include "../inc/netpbm.h"

// NetPBM

NetPBM::NetPBM (){}
NetPBM::~NetPBM (){}

int NetPBM::ditheringMessage ()
{
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
    if (choice < 1 && choice > 11){
        throw std::runtime_error("Error: Invalid choice of a dithering algorithm.");
    }
    return choice;
}
int NetPBM::hexToInt (char hex)
{
    //convert hex value to integer
    switch (hex)
    {
        case '0' : return 0; break;
        case '1' : return 1; break;
        case '2' : return 2; break;
        case '3' : return 3; break;
        case '4' : return 4; break;
        case '5' : return 5; break;
        case '6' : return 6; break;
        case '7' : return 7; break;
        case '8' : return 8; break;
        case '9' : return 9; break;
        case 'A' : return 10; break;
        case 'B' : return 11; break;
        case 'C' : return 12; break;
        case 'D' : return 13; break;
        case 'E' : return 14; break;
        case 'F' : return 15; break;        
        default : throw std::runtime_error("Error: Unknown background color.");
    }
    return -1;
        
}
void NetPBM::validateCrop(int topLeftX, int topLeftY, int& bottomRightX, int& bottomRightY)
{
    std::cout << "Top left x: " << topLeftX << std::endl;
    std::cout << "Top left y: " << topLeftY << std::endl;
    std::cout << "Bottom right x: " << bottomRightX << std::endl;
    std::cout << "Bottom right y: " << bottomRightY << std::endl;
    //if both coordinates are out of bounds the operation is not possible
    if (topLeftX < 1 || topLeftY < 1 || bottomRightX < 1 || bottomRightY < 1) {
        throw std::invalid_argument("Error: Coordinates must be positive.");
    }

    if ((topLeftX > width && bottomRightX > width) ||
        (bottomRightY > height && topLeftY > height))
    {
        throw std::runtime_error("Error: Rectangle is out of bounds. Hint: Enter top left and bottom right coordinates.");
    }

    if (topLeftX > bottomRightX) {
        throw std::runtime_error("Error: The X coordinate of top left is greater than bottom right.");
    }

    if (bottomRightY > topLeftY) {
        throw std::runtime_error("Error: The Y coordinate of bottom right is greater than top left.");
    }

    //if only one coordinate is out of bounds resize to bounds
    if (bottomRightX > width) {
        bottomRightX = width;
    }

    if (bottomRightY > height) {
        bottomRightY = height;
    }
}
int NetPBM::returnWidth()
{
    return width;
}
int NetPBM::returnHeight()
{
    return height;
}
std::vector<int> NetPBM::returnImage()
{
    return imageGrid;
}

// PBM 

Pbm::Pbm(int height, int width, std::vector<int>& imageGrid)
{
    //constructor
    this->height = height;
    this->width = width;
    this->imageGrid = imageGrid;
}
Pbm::~Pbm(){}
void Pbm::createFile(std::string bgcolor) 
{
    //create file according to bgcolor
    int pixel;
    
    if (bgcolor == "#FFFFFF"){
        pixel = 0;
    }
    else if (bgcolor == "#000000"){
        pixel = 1;
    }
    else {
        throw std::invalid_argument("Invalid background color for PBM.");
    }

    //save new file
    for (int i = 0; i < height*width; i++)
    {
        imageGrid.push_back(pixel);
    }
}
void Pbm::validateFile() 
{
    //chack if the file is valid PBM file
    if (height < 1 || width < 1)
    {
        throw std::runtime_error("Error: Invalid height or width.");
    }

    if (imageGrid.size() + 1 != height*width){
        throw std::runtime_error("Error: Height and width are inaccurate for the pixels.");
    }

    for (int i = 0; i < imageGrid.size(); i++)
    {
        if (imageGrid[i] != 0 || imageGrid[i] != 1)
        {
            throw std::runtime_error("Error: File does not contain only 1 and 0.");
        }
    }
}
void Pbm::ditherImage() 
{
    //create a Dithering object
    Dithering<Pbm> d(height, width, max, imageGrid);
    int temp = ditheringMessage();
    //dither using the object
    d.dither(temp);

    //save result in imageGrid
    imageGrid.clear();
    for (int i = 0; i < d.returnImage().size(); i++)
    {
        for (int j = 0; j < d.returnImage().at(i).size(); j++)
        {
            imageGrid.push_back(d.returnImage().at(i).at(j));
        }
    }
}
void Pbm::cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) 
{
    //validate crop parameters
    validateCrop(topLeftX, topLeftY, bottomRightX, bottomRightY);
    
    //save imageGrid to croppedImage
    std::vector<std::vector<int>> croppedImage;
    std::vector<int> line;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            line.push_back(imageGrid.at(i*width + j));
        }
        croppedImage.push_back(line);
        line.clear();
    }

    imageGrid.clear();

    //save cropped part to imageGrid
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++)
        {
            if (i < topLeftY && i > bottomRightY && j > topLeftX && j < bottomRightX)
            {
                imageGrid.push_back(croppedImage.at(i).at(j));
            }
        }
    }
    croppedImage.clear();
}
void Pbm::resizeImage(int percentage) 
{
    //update width and height
    int newWidth = width * (percentage / 100);
    int newHeight = height * (percentage / 100);
    //save image
    resizeImage(newWidth, newHeight);
}
void Pbm::resizeImage(int width, int height)
{
    //save result into scaledImage
    std::vector<int> scaledImage;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //scale
            int srcX = int( round( float(x) / float(width) * float(this->width) ) );
            int srcY = int( round( float(y) / float(width) * float(this->height) ) );
            srcX = std::min( srcX, this->width-1);
            srcY = std::min( srcY, this->height-1);
            scaledImage.push_back(imageGrid.at(this->width*srcY+srcX));
        }
    }

    //save scaled image to imageGrid
    imageGrid.clear();
    imageGrid = scaledImage;
    scaledImage.clear();

    //update width and height
    this->width = width;
    this->height = height;
}

// PGM 

Pgm::Pgm (int height, int width, int max, std::vector<int> & imageGrid)
{
    //constructor
    this->height = height;
    this->width = width;
    this->max = max;
    this->imageGrid = imageGrid;
}
Pgm::~Pgm (){}
void Pgm::createFile(std::string bgcolor)
{
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
    else {
        //create pixel
        int pixel = 0;
        for (int j = 1 ; j < 3; j++)
        {
            //convert color to integer
            char c = bgcolor.at(j);
            int temp = hexToInt(c);
            if (j % 2 == 0) {
                pixel += temp;
            }
            else {
                pixel = (16*temp);
            }
        }
        for (int i = 0; i < height*width; i++)
        {
            //save pixels
            imageGrid.push_back(pixel);
        }
    }
} 
void Pgm::validateFile() 
{
    if (height < 1 || width < 1)
    {
        throw std::runtime_error("Error: Invalid height or width.");
    }

    if (max > 65535)
    {
        throw std::runtime_error("Error: Maximum value is 65535.");
    }

    if ((imageGrid.size() + 1) != height*width){
        throw std::runtime_error("Error: Height and width are inaccurate for the pixels.");
    }

    for (int i = 0; i < imageGrid.size(); i++)
    {
        //check is every pixel is >= than max value
        if (imageGrid[i] > max){
            throw std::invalid_argument("Error: The value of the pixels is greater than the maximum.");
        }
    }
}
void Pgm::ditherImage() 
{
    //create Dithering object and use it to perform the dither
    Dithering<Pgm> d(height, width, max, imageGrid);
    int temp = ditheringMessage();
    d.dither(temp);

    //save result to imageGrid
    imageGrid.clear();
    for (int i = 0; i < d.returnImage().size(); i++)
    {
        for (int j = 0; j < d.returnImage().at(i).size(); j++)
        {
            imageGrid.push_back(d.returnImage().at(i).at(j));
        }
    }
}
void Pgm::cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) 
{
    //validate crop parameters
    validateCrop(topLeftX, topLeftY, bottomRightX, bottomRightY);
    //save result to croppedImage
    std::vector<std::vector<int>> croppedImage;
    std::vector<int> line;

    //save imageGrid to croppedImage
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            line.push_back(imageGrid.at(i*width + j));
        }
        croppedImage.push_back(line);
        line.clear();
    }

    imageGrid.clear();

    //save cropped part to imageGrid
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++)
        {
            if (i < topLeftY && i > bottomRightY && j > topLeftX && j < bottomRightX)
            {
                imageGrid.push_back(croppedImage.at(i).at(j));
            }
        }
    }
    croppedImage.clear();
}
void Pgm::resizeImage(int percentage) 
{
    //update width and height to match the percentage
    int newWidth = width * (percentage / 100);
    int newHeight = height * (percentage / 100);
    //resize image
    resizeImage(newWidth, newHeight);
}
void Pgm::resizeImage(int width, int height)
{
    //save result into scaledImage
    std::vector<int> scaledImage;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //scale
            int srcX = int( round( float(x) / float(width) * float(this->width) ) );
            int srcY = int( round( float(y) / float(width) * float(this->height) ) );
            srcX = std::min( srcX, this->width-1);
            srcY = std::min( srcY, this->height-1);
            std::cout << x << " " << y << std::endl;
            std::cout << srcX << " " << srcY << std::endl;
            std ::cout << imageGrid.at(this->width*srcY+srcX) << std::endl;
            scaledImage.push_back(imageGrid.at(this->width*srcY+srcX));
        }
    }

    //save result into ImageGrid
    imageGrid.clear();
    imageGrid = scaledImage;
    scaledImage.clear();

    //update width and height
    this->width = width;
    this->height = height;
}

// PPM

Ppm::Ppm (int height, int width, int max, std::vector<int> & imageGrid)
{
    //constructor
    this->height = height;
    this->width = width;
    this->max = max;
    this->imageGrid = imageGrid;
}
Ppm::~Ppm(){}
void Ppm::createFile(std::string bgcolor)
{
    //create rgb triple
    int rgb [3];
    int pixel = 0;
    int temp = 0;
    //create individual colors
    for (int i = 1 ; i < 7; i++)
    {
        char c = bgcolor.at(i);
        temp = hexToInt(c);
        if (i % 2 == 0) {
            pixel += temp;
            rgb[(i/2)-1] = pixel;
        }
        else {
            pixel = (16*temp);
        }
    }
    //save coloured pixels
    for (int i = 0; i < height*width*3; i++)
    {
        if (i % 2 == 0){
            imageGrid.push_back(rgb[0]);
        }
        else if (i % 2 == 1){
            imageGrid.push_back(rgb[1]);
        }
        else {
            imageGrid.push_back(rgb[2]);
        }
    }
}
void Ppm::validateFile()
{
    //check if file is valid PPM file
    if (height < 1 || width < 1)
    {
        throw std::runtime_error("Error: Invalid height or width.");
    }

    if ((imageGrid.size() + 1)*3 != height*width){
        throw std::runtime_error("Error: Height and width are inaccurate for the pixels.");
    }

    if (max > 65535)
    {
        throw std::runtime_error("Error: Maximum value is 65535.");
    }

    for (int i = 0; i < imageGrid.size(); i++)
    {
        if (imageGrid[i] > max){
            throw std::invalid_argument("The value of the pixels is greater than the maximum.");
        }
    }
}
void Ppm::ditherImage()
{
    //use Dithering object to dither the image
    Dithering<Ppm> d(height, width, max, imageGrid);
    int temp = ditheringMessage();
    d.dither(temp);

    //save result
    imageGrid.clear();
    for (int i = 0; i < d.returnImage().size(); i++)
    {
        for (int j = 0; j < d.returnImage().at(i).size(); j++)
        {
            imageGrid.push_back(d.returnImage().at(i).at(j));
        }
    }
}
void Ppm::cropImage(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)
{
    //validate crop parameters
    validateCrop(topLeftX, topLeftY, bottomRightX, bottomRightY);

    //save result to croppedImage
    std::vector<std::vector<int>> croppedImage;
    std::vector<int> line;

    //save imageGrid to croppedImage
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            line.push_back(imageGrid.at(i*width + j*3));
            line.push_back(imageGrid.at(i*width + j*3 + 1));
            line.push_back(imageGrid.at(i*width + j*3 + 2));
        }
        croppedImage.push_back(line);
        line.clear();
    }

    imageGrid.clear();

    //save cropped part to imageGrid
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width*3; j+=3)
        {
            if (i < topLeftY && i > bottomRightY && j > topLeftX*3 && j < bottomRightX*3)
            {
                imageGrid.push_back(croppedImage.at(i).at(j));
                imageGrid.push_back(croppedImage.at(i).at(j+1));
                imageGrid.push_back(croppedImage.at(i).at(j+2));
            }
        }
    }
    croppedImage.clear();
}
void Ppm::resizeImage(int percentage) 
{
    //update height and width
    int newWidth = width * (percentage / 100);
    int newHeight = height * (percentage / 100);
    //resize image
    resizeImage(newWidth, newHeight);
}
void Ppm::resizeImage(int width, int height)
{
    //save scaledImage into scaledImage
    std::vector<int> scaledImage;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //scale
            int srcX = int( round( float(x) / float(width) * float(this->width) ) );
            int srcY = int( round( float(y) / float(width) * float(this->height) ) );
            srcX = std::min( srcX, this->width-1);
            srcY = std::min( srcY, this->height-1);
            //save new image
            scaledImage.push_back(imageGrid.at(this->width*srcY+srcX));
        }
    }

    imageGrid.clear();
    //save scaledImage into imageGrid
    imageGrid = scaledImage;
    scaledImage.clear();

    //update width and height
    this->width = width;
    this->height = height;
}