#include "../inc/ditheringRGB.h"

DitheringRGB::DitheringRGB()
{
    Image& image = Image::getInstance();

    this->height = image.getHeight();
    this->width = image.getWidth();
    this->max = image.getMax();

    //save Image into newImage
    std::vector<int> line;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width * 3; j += 3)
        {
            for (int z = 0; z < 3; z++)
            {
                line.push_back(image.getPixels().at(i * width * 3 + j + z));
            }
        }
        newImage.push_back(line);
        line.clear();
    }
}

DitheringRGB::~DitheringRGB() {}

///
/// @param type - the type of Dithering
void DitheringRGB::dither(int type) {
    //choose dither type
    if (type == 1)      {floydSteinberg();}
    else if (type == 2) {falseFloydSteinberg();}
    else if (type == 3) {jarvisJudiceNinke();}
    else if (type == 4) {stucki();}
    else if (type == 5) {atkinson();}
    else if (type == 6) {burkes();}
    else if (type == 7) {sierra();}
    else if (type == 8) {twoRowSierra();}
    else if (type == 9) {sierraLite();}
    else if (type == 10) {ordered4x4BayerMatrix();}
    else if (type == 11) {ordered8x8BayerMatrix();}
    else {throw std::runtime_error("Error: Unknown dither type.");}
}

void DitheringRGB::floydSteinberg()
{
    /*
    Dither according to the Floyd-Steinberg matrix:
            X   7
        3   5   1
          (1/16)
    */

    int oldPixel; //old pixel value
    int newPixel; //new pixel value
    int error; //error value

    for (int y = 0; y < height - 1; y++)
    {
         for (int x = 3; x < (width * 3) - 5; x += 3)
         {
             for (int z = 0; z < 3; z++) {
                 oldPixel = newImage[y][z + x];
                 newPixel = (oldPixel > (max / 2)) ? max : 0;
                 newImage[y][z + x] = newPixel;
                 error = oldPixel - newPixel;
                 newImage[y][z + x + 3] += ((error * 7) / 16);
                 newImage[y + 1][z + x - 3] += ((error * 3) / 16);
                 newImage[y + 1][z + x] += ((error * 5) / 16);
                 newImage[y + 1][z + x + 3] += ((error * 1) / 16);
             }
        }
    }
    newImageToImage();
}

void DitheringRGB::falseFloydSteinberg()
{
    /*
   Dither according to the False Floyd-Steinberg matrix:
       X   3
       3   2
       (1/8)
   */

    int oldPixel; //old pixel value
    int newPixel; //new pixel value
    int error; //error value

    for (int y = 0; y < height - 1; y++)
    {
        for (int x = 0; x < (width * 3) - 5; x += 3)
        {
            for (int z = 0; z < 3; z++)
            {
                oldPixel = newImage[y][z + x];
                newPixel = (oldPixel > (max / 2)) ? max : 0;
                newImage[y][z + x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][z + x + 3] += ((error * 3) / 8);
                newImage[y + 1][z + x] += ((error * 3) / 8);
                newImage[y + 1][z + x + 3] += ((error * 2) / 8);
            }
        }
    }

    newImageToImage();
}

void DitheringRGB::jarvisJudiceNinke()
{
    /*
   Dither according to the Jarvis, Judice, and Ninke matrix:
            X   7   5
    3   5   7   5   3
    1   3   5   3   1
          (1/48)
   */

    int oldPixel; //old pixel value
    int newPixel; //new pixel value
    int error; //error value

    for (int y = 0; y < height - 2; y++)
    {
        for (int x = 6; x < (width * 3) - 8; x += 3)
        {
            for (int z = 0; z < 3; z++)
            {
                oldPixel = newImage[y][z + x];
                newPixel = (oldPixel > (max / 2)) ? max : 0;
                newImage[y][z + x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][z + x + 3] += (error * 7) / 48;
                newImage[y][z + x + 6] += (error * 5) / 48;
                //second row
                newImage[y + 1][z + x - 6] += (error * 3) / 48;
                newImage[y + 1][z + x - 3] += (error * 5) / 48;
                newImage[y + 1][z + x] += (error * 7) / 48;
                newImage[y + 1][z + x + 3] += (error * 5) / 48;
                newImage[y + 1][z + x + 6] += (error * 3) / 48;
                //third row
                newImage[y + 2][z + x - 6] += (error * 1) / 48;
                newImage[y + 2][z + x - 3] += (error * 3) / 48;
                newImage[y + 2][z + x] += (error * 5) / 48;
                newImage[y + 2][z + x + 3] += (error * 3) / 48;
                newImage[y + 2][z + x + 6] += (error * 1) / 48;
            }
        }
    }
    newImageToImage();
}

void DitheringRGB::stucki()
{
    /*
   Dither according to the Stucki matrix:
            X   8   4
    2   4   8   4   2
    1   2   4   2   1
          (1/42)
   */
    int oldPixel;//old pixel value
    int newPixel;//new pixel value
    int error;//error value


    for (int y = 0; y < height - 2; y++)
    {
        for (int x = 6; x < (width * 3) - 8; x += 3)
        {
            for (int z = 0; z < 3; z++)
            {
                oldPixel = newImage[y][z + x];
                newPixel = (oldPixel > (max / 2)) ? max : 0;
                newImage[y][z + x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][z + x + 3] += (error * 8) / 42;
                newImage[y][z + x + 6] += (error * 4) / 42;
                //second row
                newImage[y + 1][z + x - 6] += (error * 2) / 42;
                newImage[y + 1][z + x - 3] += (error * 4) / 42;
                newImage[y + 1][z + x] += (error * 8) / 42;
                newImage[y + 1][z + x + 3] += (error * 4) / 42;
                newImage[y + 1][z + x + 6] += (error * 2) / 42;
                //third row
                newImage[y + 2][z + x - 6] += (error * 1) / 42;
                newImage[y + 2][z + x - 3] += (error * 2) / 42;
                newImage[y + 2][z + x] += (error * 4) / 42;
                newImage[y + 2][z + x + 3] += (error * 2) / 42;
                newImage[y + 2][z + x + 6] += (error * 1) / 42;
            }
        }
    }

    newImageToImage();
}

void DitheringRGB::atkinson()
{
    /*
   Dither according to the Atkinson matrix:
       X   1   1
   1   1   1
       1
     (1/8)
   */
    int oldPixel; //old pixel value
    int newPixel; //new pixel value
    int error; //error value

    for (int y = 0; y < height - 2; y++)
    {
        for (int x = 3; x < (width * 3) - 8; x += 3)
        {
            for (int z = 0; z < 3; z++)
            {
                oldPixel = newImage[y][z + x];
                newPixel = (oldPixel > (max / 2)) ? max : 0;
                newImage[y][z + x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][z + x + 3] += error / 8;
                newImage[y][z + x + 6] += error / 8;
                //second row
                newImage[y + 1][z + x - 3] += error / 8;
                newImage[y + 1][z + x] += error / 8;
                newImage[y + 1][z + x + 3] += error / 8;
                //third row
                newImage[y + 2][z + x] += error / 8;
            }
        }
    }

    newImageToImage();
}

void DitheringRGB::burkes()
{
    /*
    Dither according to the Burkes matrix:
             X   8   4
     2   4   8   4   2
           (1/32)
    */
    int oldPixel; //old pixel value
    int newPixel; //new pixel value
    int error; //error value

    for (int y = 0; y < height - 1; y++)
    {
        for (int x = 6; x < (width * 3) - 8; x += 3)
        {
            for (int z = 0; z < 3; z++)
            {
                oldPixel = newImage[y][z + x];
                newPixel = (oldPixel > (max / 2)) ? max : 0;
                newImage[y][z + x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][z + x + 3] += (error * 8) / 32;
                newImage[y][z + x + 6] += (error * 4) / 32;
                //second row
                newImage[y + 1][z + x - 6] += (error * 2) / 32;
                newImage[y + 1][z + x - 3] += (error * 4) / 32;
                newImage[y + 1][z + x] += (error * 8) / 32;
                newImage[y + 1][z + x + 3] += (error * 4) / 32;
                newImage[y + 1][z + x + 6] += (error * 2) / 32;
            }
        }
    }

    newImageToImage();
}

void DitheringRGB::sierra()
{
    /*
    Dither according to the Sierra matrix:
            X   5   3
     2   4  5   4   2
         2  3   2
          (1/32)
    */
    int oldPixel; //old pixel value
    int newPixel; //new pixel value
    int error; //error value

    for (int y = 0; y < height - 2; y++)
    {
        for (int x = 6; x < (width * 3) - 8; x += 3)
        {
            for (int z = 0; z < 3; z++)
            {
                oldPixel = newImage[y][z + x];
                newPixel = (oldPixel > (max / 2)) ? max : 0;
                newImage[y][z + x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][z + x + 3] += error * 5 / 42;
                newImage[y][z + x + 6] += error * 3 / 42;
                //second row
                newImage[y + 1][z + x - 6] += error * 2 / 42;
                newImage[y + 1][z + x - 3] += error * 4 / 42;
                newImage[y + 1][z + x] += error * 5 / 42;
                newImage[y + 1][z + x + 3] += error * 4 / 42;
                newImage[y + 1][z + x + 6] += error * 2 / 42;
                //third row
                newImage[y + 2][z + x - 3] += error * 2 / 42;
                newImage[y + 2][z + x] += error * 3 / 42;
                newImage[y + 2][z + x + 3] += error * 2 / 42;
            }
        }
    }

    newImageToImage();
}

void DitheringRGB::twoRowSierra()
{
    /*
    Dither according to the Two-Row Sierra matrix:
            X   4   3
    1   2   3   2   1
          (1/16)
    */
    int oldPixel; //old pixel value
    int newPixel; //new pixel value
    int error; //error value

    for (int y = 0; y < height - 1; y++)
    {
        for (int x = 6; x < (width * 3) - 8; x += 3)
        {
            for (int z = 0; z < 3; z++)
            {
                oldPixel = newImage[y][z + x];
                newPixel = (oldPixel > (max / 2)) ? max : 0;
                newImage[y][z + x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][z + x + 3] += (error * 4) / 16;
                newImage[y][z + x + 6] += (error * 3) / 16;
                //second row
                newImage[y + 1][z + x - 6] += (error * 1) / 16;
                newImage[y + 1][z + x - 3] += (error * 2) / 16;
                newImage[y + 1][z + x] += (error * 3) / 16;
                newImage[y + 1][z + x + 3] += (error * 2) / 16;
                newImage[y + 1][z + x + 6] += (error * 1) / 16;
            }
        }
    }

    newImageToImage();
}

void DitheringRGB::sierraLite()
{
    /*
    Dither according to the Sierra Lite matrix:
            X   2
        1   1
          (1/4)
    */
    int oldPixel; //old pixel value
    int newPixel; //new pixel value
    int error; //error value

    for (int y = 0; y < height - 1; y++)
    {
        for (int x = 3; x < (width * 3) - 5; x += 3)
        {
            for (int z = 0; z < 3; z++)
            {
                oldPixel = newImage[y][z + x];
                newPixel = (oldPixel > (max / 2)) ? max : 0;
                newImage[y][z + x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][z + x + 3] += error * 2 / 4;
                //second row
                newImage[y + 1][z + x - 3] += error * 1 / 4;
                newImage[y + 1][z + x] += error * 1 / 4;
            }
        }
    }

    newImageToImage();
}

void DitheringRGB::ordered4x4BayerMatrix()
{
    //dithering according to the Bayer 4x4 matrix
    unsigned int bayer4x4[4][4] = {{1,  9,  3,  11},
                                   {13, 5,  15, 7},
                                   {4,  12, 2,  10},
                                   {16, 8,  14, 6}};

    int channelValues = 2;
    int offset = (4 * (4 / 2) - 0.5); //calculate offset
    int error = max / channelValues / 16; //error value

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width * 3; x += 3)
        {
            //Red pixel
            int& pixel1 = newImage[y][x];
            pixel1 += (error * (bayer4x4[x % 16][y % 16] - offset));
            pixel1 = round(channelValues * pixel1 / 255) * (255 / channelValues);
            //Green pixel
            int& pixel2 = newImage[y][x + 1];
            pixel2 += (error * (bayer4x4[x % 16][y % 16] - offset));
            pixel2 = round(channelValues * pixel2 / 255) * (255 / channelValues);
            //Green pixel
            int& pixel3 = newImage[y][x + 2];
            pixel3 += (error * (bayer4x4[x % 16][y % 16] - offset));
            pixel3 = round(channelValues * pixel3 / 255) * (255 / channelValues);
        }
    }

    newImageToImage();
}

void DitheringRGB::ordered8x8BayerMatrix()
{
    //dither according to the Bayer 8x8 matrix
    unsigned int bayer8x8[8][8] = {{0,  32, 8,  40, 2,  34, 10, 42},
                                   {48, 16, 56, 24, 50, 18, 58, 26},
                                   {12, 44, 4,  36, 14, 46, 6,  38},
                                   {60, 28, 52, 20, 62, 30, 54, 22},
                                   {3,  35, 11, 43, 1,  33, 9,  41},
                                   {51, 19, 59, 27, 49, 17, 57, 25},
                                   {15, 47, 7,  39, 13, 45, 5,  37},
                                   {63, 31, 55, 23, 61, 29, 53, 21}};


    int channelValues = 2;
    int offset = (8 * (8 / 2) - 0.5); //calculate offset
    int error = max / channelValues / 64; //error value

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width * 3; x += 3)
        {
            //Red pixel
            int& pixel1 = newImage[y][x];
            pixel1 += (error * (bayer8x8[x % 64][y % 64] - offset));
            pixel1 = round(channelValues * pixel1 / 255) * (255 / channelValues);
            //Green pixel
            int& pixel2 = newImage[y][x + 1];
            pixel2 += (error * (bayer8x8[x % 64][y % 64] - offset));
            pixel2 = round(channelValues * pixel2 / 255) * (255 / channelValues);
            //Green pixel
            int& pixel3 = newImage[y][x + 2];
            pixel3 += (error * (bayer8x8[x % 64][y % 64] - offset));
            pixel3 = round(channelValues * pixel3 / 255) * (255 / channelValues);
        }
    }
    newImageToImage();
}

