#include "../inc/dithering.h"

template<class A>
Dithering<A>::Dithering (int height, int width, int man, std::vector<int> imageGrid)
{
    this->height = height;
    this->width = width;
    this->max = max;

    std::vector<int> line;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (imageGrid.size() == width*height){
                line.push_back(imageGrid.at(i*width + j));
            }
            else if (imageGrid.size() == width*height*3){
                line.push_back(imageGrid.at(i*width + j*3));
                line.push_back(imageGrid.at(i*width + j*3 + 1));
                line.push_back(imageGrid.at(i*width + j*3 + 2));
            }
        }
        newImage.push_back(line);
        line.clear();
    }
}

template<class A>
void Dithering<A>::dither(int type)
{
    switch (type)
    {
        case 1 : floydSteinberg();        break;
        case 2 : falseFloydSteinberg();   break;
        case 3 : jarvisJudiceNinke();     break;
        case 4 : stucki();                break;
        case 5 : atkinson();              break;
        case 6 : burkes();                break;
        case 7 : sierra();                break;
        case 8 : twoRowSierra();          break;
        case 9 : sierraLite();            break;
        case 10: ordered4x4BayerMatrix(); break;
        case 11: ordered4x4BayerMatrix(); break;
        default : throw std::runtime_error("Error: Unknown dither type."); break;
    }   
}

template<class A>
std::vector<std::vector<int>> Dithering<A>::returnImage()
{
    return newImage;
}

template<class A>
void Dithering<A>::floydSteinberg()
{
    int oldPixel;
    int newPixel;
    int error;

    for (int y = 0; y < height-1; y++)
    {
        if (width == newImage.at(0).size()){
            for (int x = 1; x < width-1; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+1]   += error * 7 / 16;
                newImage[y+1][x-1] += error * 3 / 16;
                newImage[y+1][x]   += error * 5 / 16;
                newImage[y+1][x+1] += error * 1 / 16;
            }   
        }
        else {
            for (int x = 3; x < width-3; x+=3)
            {
                //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+3]   += error * 7 / 16;
                newImage[y+1][x-3] += error * 3 / 16;
                newImage[y+1][x]   += error * 5 / 16;
                newImage[y+1][x+3] += error * 1 / 16;
                //Green pixel
                oldPixel = newImage[y][x+1];
                newPixel = round(oldPixel/max);
                newImage[y][x+1] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+4]   += error * 7 / 16;
                newImage[y+1][x-4] += error * 3 / 16;
                newImage[y+1][x+1] += error * 5 / 16;
                newImage[y+1][x+4] += error * 1 / 16;
                //Blue pixel
                oldPixel = newImage[y][x+2];
                newPixel = round(oldPixel/max);
                newImage[y][x+2] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+5]   += error * 7 / 16;
                newImage[y+1][x-5] += error * 3 / 16;
                newImage[y+1][x+2] += error * 5 / 16;
                newImage[y+1][x+5] += error * 1 / 16;
            }
        }
    }
    
}

template<class A>
void Dithering<A>::falseFloydSteinberg()
{
    int oldPixel;
    int newPixel;
    int error;

    for (int y = 0; y < height-1; y++)
    {
        if (width == newImage.at(0).size()){
            for (int x = 0; x < width-1; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+1]   += error * 3 / 8;
                newImage[y+1][x]   += error * 3 / 8;
                newImage[y+1][x+1] += error * 2 / 8;
            }
        }
        else {
            for (int x = 0; x < width-3; x+=3)
            {
                //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+3]   += error * 3 / 8;
                newImage[y+1][x]   += error * 3 / 8;
                newImage[y+1][x+3] += error * 2 / 8;
                //Green pixel
                oldPixel = newImage[y][x+1];
                newPixel = round(oldPixel/max);
                newImage[y][x+1] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+4]   += error * 3 / 8;
                newImage[y+1][x+1] += error * 3 / 8;
                newImage[y+1][x+4] += error * 2 / 8;
                //Blue pixel
                oldPixel = newImage[y][x+2];
                newPixel = round(oldPixel/max);
                newImage[y][x+2] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+5]   += error * 3 / 8;
                newImage[y+1][x+2] += error * 3 / 8;
                newImage[y+1][x+5] += error * 2 / 8;
            }
        }
    }
}

template<class A>
void Dithering<A>::jarvisJudiceNinke()
{
    int oldPixel;
    int newPixel;
    int error;

    for (int y = 0; y < height-2; y++)
    {
        if (width == newImage.at(0).size()){
            for (int x = 2; x < width-2; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+1]   += error * 7 / 48;
                newImage[y][x+2]   += error * 5 / 48;
                newImage[y+1][x-2] += error * 3 / 48;
                newImage[y+1][x-1] += error * 5 / 48;
                newImage[y+1][x]   += error * 7 / 48;
                newImage[y+1][x+1] += error * 5 / 48;
                newImage[y+1][x+2] += error * 3 / 48;
                newImage[y+2][x-2] += error * 1 / 48;
                newImage[y+2][x-1] += error * 3 / 48;
                newImage[y+2][x]   += error * 5 / 48;
                newImage[y+2][x+1] += error * 3 / 48;
                newImage[y+2][x+2] += error * 1 / 48;
            }
        }
        else {
            for (int x = 6; x < width-6; x+=3)
            {
                //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+3]   += error * 7 / 48;
                newImage[y][x+6]   += error * 5 / 48;
                newImage[y+1][x-6] += error * 3 / 48;
                newImage[y+1][x-3] += error * 5 / 48;
                newImage[y+1][x]   += error * 7 / 48;
                newImage[y+1][x+3] += error * 5 / 48;
                newImage[y+1][x+6] += error * 3 / 48;
                newImage[y+2][x-6] += error * 1 / 48;
                newImage[y+2][x-3] += error * 3 / 48;
                newImage[y+2][x]   += error * 5 / 48;
                newImage[y+2][x+3] += error * 3 / 48;
                newImage[y+2][x+6] += error * 1 / 48;
                //Green pixel
                oldPixel = newImage[y][x+1];
                newPixel = round(oldPixel/max);
                newImage[y][x+1] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+4]   += error * 7 / 48;
                newImage[y][x+7]   += error * 5 / 48;
                newImage[y+1][x-7] += error * 3 / 48;
                newImage[y+1][x-4] += error * 5 / 48;
                newImage[y+1][x+1] += error * 7 / 48;
                newImage[y+1][x+4] += error * 5 / 48;
                newImage[y+1][x+7] += error * 3 / 48;
                newImage[y+2][x-7] += error * 1 / 48;
                newImage[y+2][x-4] += error * 3 / 48;
                newImage[y+2][x+1] += error * 5 / 48;
                newImage[y+2][x+4] += error * 3 / 48;
                newImage[y+2][x+7] += error * 1 / 48;
                //Blue pixel
                oldPixel = newImage[y][x+2];
                newPixel = round(oldPixel/max);
                newImage[y][x+2] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+5]   += error * 7 / 48;
                newImage[y][x+8]   += error * 5 / 48;
                newImage[y+1][x-8] += error * 3 / 48;
                newImage[y+1][x-5] += error * 5 / 48;
                newImage[y+1][x+2] += error * 7 / 48;
                newImage[y+1][x+5] += error * 5 / 48;
                newImage[y+1][x+8] += error * 3 / 48;
                newImage[y+2][x-8] += error * 1 / 48;
                newImage[y+2][x-5] += error * 3 / 48;
                newImage[y+2][x+2] += error * 5 / 48;
                newImage[y+2][x+5] += error * 3 / 48;
                newImage[y+2][x+8] += error * 1 / 48;
            }
        }
    }
}

template<class A>
void Dithering<A>::stucki()
{
    int oldPixel;
    int newPixel;
    int error;

    for (int y = 0; y < height-2; y++)
    {
        if (width == newImage.at(0).size()){
            for (int x = 2; x < width-2; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+1]   += error * 8 / 42;
                newImage[y][x+2]   += error * 4 / 42;
                newImage[y+1][x-2] += error * 2 / 42;
                newImage[y+1][x-1] += error * 4 / 42;
                newImage[y+1][x]   += error * 8 / 42;
                newImage[y+1][x+1] += error * 4 / 42;
                newImage[y+1][x+2] += error * 2 / 42;
                newImage[y+2][x-2] += error * 1 / 42;
                newImage[y+2][x-1] += error * 2 / 42;
                newImage[y+2][x]   += error * 4 / 42;
                newImage[y+2][x+1] += error * 2 / 42;
                newImage[y+2][x+2] += error * 1 / 42;
            }
        }
        else {
            for (int x = 6; x < width-6; x+=3)
            {
                //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+3]   += error * 8 / 42;
                newImage[y][x+6]   += error * 4 / 42;
                newImage[y+1][x-6] += error * 2 / 42;
                newImage[y+1][x-3] += error * 4 / 42;
                newImage[y+1][x]   += error * 8 / 42;
                newImage[y+1][x+3] += error * 4 / 42;
                newImage[y+1][x+6] += error * 2 / 42;
                newImage[y+2][x-6] += error * 1 / 42;
                newImage[y+2][x-3] += error * 2 / 42;
                newImage[y+2][x]   += error * 4 / 42;
                newImage[y+2][x+3] += error * 2 / 42;
                newImage[y+2][x+6] += error * 1 / 42;
                //Green pixel
                oldPixel = newImage[y][x+1];
                newPixel = round(oldPixel/max);
                newImage[y][x+1] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+4]   += error * 8 / 42;
                newImage[y][x+7]   += error * 4 / 42;
                newImage[y+1][x-7] += error * 2 / 42;
                newImage[y+1][x-4] += error * 4 / 42;
                newImage[y+1][x+1] += error * 8 / 42;
                newImage[y+1][x+4] += error * 4 / 42;
                newImage[y+1][x+7] += error * 2 / 42;
                newImage[y+2][x-7] += error * 1 / 42;
                newImage[y+2][x-4] += error * 2 / 42;
                newImage[y+2][x+1] += error * 4 / 42;
                newImage[y+2][x+4] += error * 2 / 42;
                newImage[y+2][x+7] += error * 1 / 42;
                //Blue pixel
                oldPixel = newImage[y][x+2];
                newPixel = round(oldPixel/max);
                newImage[y][x+2] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+5]   += error * 8 / 42;
                newImage[y][x+8]   += error * 4 / 42;
                newImage[y+1][x-8] += error * 2 / 42;
                newImage[y+1][x-5] += error * 4 / 42;
                newImage[y+1][x+2] += error * 8 / 42;
                newImage[y+1][x+5] += error * 4 / 42;
                newImage[y+1][x+8] += error * 2 / 42;
                newImage[y+2][x-8] += error * 1 / 42;
                newImage[y+2][x-5] += error * 2 / 42;
                newImage[y+2][x+2] += error * 4 / 42;
                newImage[y+2][x+5] += error * 2 / 42;
                newImage[y+2][x+8] += error * 1 / 42;
            }
        }
    }
}

template<class A>
void Dithering<A>::atkinson()
{
    int oldPixel;
    int newPixel;
    int error;

    for (int y = 0; y < height-2; y++)
    {
        if (width == newImage.at(0).size()){
            for (int x = 0; x < width-2; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+1]   += error / 8;
                newImage[y][x+2]   += error / 8;
                newImage[y+1][x-1] += error / 8;
                newImage[y+1][x]   += error / 8;
                newImage[y+1][x+1] += error / 8;
                newImage[y+2][x]   += error / 8;
            }
        }
        else {
            for (int x = 3; x < width-6; x+=3)
            {
                //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+3]   += error / 8;
                newImage[y][x+6]   += error / 8;
                newImage[y+1][x-3] += error / 8;
                newImage[y+1][x]   += error / 8;
                newImage[y+1][x+3] += error / 8;
                newImage[y+2][x]   += error / 8;
                //Green pixel
                oldPixel = newImage[y][x+1];
                newPixel = round(oldPixel/max);
                newImage[y][x+1] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+4]   += error / 8;
                newImage[y][x+7]   += error / 8;
                newImage[y+1][x-4] += error / 8;
                newImage[y+1][x+1] += error / 8;
                newImage[y+1][x+4] += error / 8;
                newImage[y+2][x+1] += error / 8;
                //Blue pixel
                oldPixel = newImage[y][x+2];
                newPixel = round(oldPixel/max);
                newImage[y][x+2] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+5]   += error / 8;
                newImage[y][x+8]   += error / 8;
                newImage[y+1][x-5] += error / 8;
                newImage[y+1][x+2] += error / 8;
                newImage[y+1][x+5] += error / 8;
                newImage[y+2][x+2] += error / 8;
            }
        }
    }
}

template<class A>
void Dithering<A>::burkes()
{
    int oldPixel;
    int newPixel;
    int error;

    for (int y = 0; y < height-1; y++)
    {
        if (width == newImage.at(0).size()){
            for (int x = 2; x < width-2; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+1]   += error * 8 / 32;
                newImage[y][x+2]   += error * 4 / 32;
                newImage[y+1][x-2] += error * 2 / 32;
                newImage[y+1][x-1] += error * 4 / 32;
                newImage[y+1][x]   += error * 8 / 32;
                newImage[y+1][x+1] += error * 4 / 32;
                newImage[y+1][x+2] += error * 2 / 32;
            }
        }
        else {
            for (int x = 6; x < width-6; x+=3)
            {
                //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+3]   += error * 8 / 32;
                newImage[y][x+6]   += error * 4 / 32;
                newImage[y+1][x-6] += error * 2 / 32;
                newImage[y+1][x-3] += error * 4 / 32;
                newImage[y+1][x]   += error * 8 / 32;
                newImage[y+1][x+3] += error * 4 / 32;
                newImage[y+1][x+6] += error * 2 / 32;
                //Green pixel
                oldPixel = newImage[y][x+1];
                newPixel = round(oldPixel/max);
                newImage[y][x+1] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+4]   += error * 8 / 32;
                newImage[y][x+7]   += error * 4 / 32;
                newImage[y+1][x-7] += error * 2 / 32;
                newImage[y+1][x-4] += error * 4 / 32;
                newImage[y+1][x+1] += error * 8 / 32;
                newImage[y+1][x+4] += error * 4 / 32;
                newImage[y+1][x+7] += error * 2 / 32;
                //Blue pixel
                oldPixel = newImage[y][x+2];
                newPixel = round(oldPixel/max);
                newImage[y][x+2] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+5]   += error * 8 / 32;
                newImage[y][x+8]   += error * 4 / 32;
                newImage[y+1][x-8] += error * 2 / 32;
                newImage[y+1][x-5] += error * 4 / 32;
                newImage[y+1][x+2] += error * 8 / 32;
                newImage[y+1][x+5] += error * 4 / 32;
                newImage[y+1][x+8] += error * 2 / 32;
            }
        }
    }
}

template<class A>
void Dithering<A>::sierra()
{
    int oldPixel;
    int newPixel;
    int error;

    for (int y = 0; y < height-2; y++)
    {
        if (width == newImage.at(0).size()){
            for (int x = 2; x < width-2; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+1]   += error * 5 / 32;
                newImage[y][x+2]   += error * 3 / 32;
                newImage[y+1][x-2] += error * 2 / 32;
                newImage[y+1][x-1] += error * 4 / 32;
                newImage[y+1][x]   += error * 5 / 32;
                newImage[y+1][x+1] += error * 4 / 32;
                newImage[y+1][x+2] += error * 2 / 32;
                newImage[y+2][x-1] += error * 2 / 32;
                newImage[y+2][x]   += error * 3 / 32;
                newImage[y+2][x+1] += error * 2 / 32;
                
            }
        }
        else {
            for (int x = 6; x < width-6; x+=3)
            {
                //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+3]   += error * 5 / 42;
                newImage[y][x+6]   += error * 3 / 42;
                newImage[y+1][x-6] += error * 2 / 42;
                newImage[y+1][x-3] += error * 4 / 42;
                newImage[y+1][x]   += error * 5 / 42;
                newImage[y+1][x+3] += error * 4 / 42;
                newImage[y+1][x+6] += error * 2 / 42;
                newImage[y+2][x-3] += error * 2 / 42;
                newImage[y+2][x]   += error * 3 / 42;
                newImage[y+2][x+3] += error * 2 / 42;
                //Green pixel
                oldPixel = newImage[y][x+1];
                newPixel = round(oldPixel/max);
                newImage[y][x+1] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+4]   += error * 5 / 42;
                newImage[y][x+7]   += error * 3 / 42;
                newImage[y+1][x-7] += error * 2 / 42;
                newImage[y+1][x-4] += error * 4 / 42;
                newImage[y+1][x+1] += error * 5 / 42;
                newImage[y+1][x+4] += error * 4 / 42;
                newImage[y+1][x+7] += error * 2 / 42;
                newImage[y+2][x-4] += error * 2 / 42;
                newImage[y+2][x+1] += error * 3 / 42;
                newImage[y+2][x+4] += error * 2 / 42;
                //Blue pixel
                oldPixel = newImage[y][x+2];
                newPixel = round(oldPixel/max);
                newImage[y][x+2] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+5]   += error * 5 / 42;
                newImage[y][x+8]   += error * 3 / 42;
                newImage[y+1][x-8] += error * 2 / 42;
                newImage[y+1][x-5] += error * 4 / 42;
                newImage[y+1][x+2] += error * 5 / 42;
                newImage[y+1][x+5] += error * 4 / 42;
                newImage[y+1][x+8] += error * 2 / 42;
                newImage[y+2][x-5] += error * 2 / 42;
                newImage[y+2][x+2] += error * 3 / 42;
                newImage[y+2][x+5] += error * 2 / 42;
            }
        }
    }
}

template<class A>
void Dithering<A>::twoRowSierra()
{
    int oldPixel;
    int newPixel;
    int error;

    for (int y = 0; y < height-1; y++)
    {
        if (width == newImage.at(0).size()){
            for (int x = 2; x < width-2; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+1]   += error * 4 / 16;
                newImage[y][x+2]   += error * 3 / 16;
                newImage[y+1][x-2] += error * 1 / 16;
                newImage[y+1][x-1] += error * 2 / 16;
                newImage[y+1][x]   += error * 3 / 16;
                newImage[y+1][x+1] += error * 2 / 16;
                newImage[y+1][x+2] += error * 1 / 16;
            }
        }
        else {
            for (int x = 6; x < width-6; x+=3)
            {
                //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+3]   += error * 4 / 16;
                newImage[y][x+6]   += error * 3 / 16;
                newImage[y+1][x-6] += error * 1 / 16;
                newImage[y+1][x-3] += error * 2 / 16;
                newImage[y+1][x]   += error * 3 / 16;
                newImage[y+1][x+3] += error * 2 / 16;
                newImage[y+1][x+6] += error * 1 / 16;
                //Green pixel
                oldPixel = newImage[y][x+1];
                newPixel = round(oldPixel/max);
                newImage[y][x+1] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+4]   += error * 4 / 16;
                newImage[y][x+7]   += error * 3 / 16;
                newImage[y+1][x-7] += error * 1 / 16;
                newImage[y+1][x-4] += error * 2 / 16;
                newImage[y+1][x+1] += error * 3 / 16;
                newImage[y+1][x+4] += error * 2 / 16;
                newImage[y+1][x+7] += error * 1 / 16;
                //Blue pixel
                oldPixel = newImage[y][x+2];
                newPixel = round(oldPixel/max);
                newImage[y][x+2] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+5]   += error * 4 / 16;
                newImage[y][x+8]   += error * 3 / 16;
                newImage[y+1][x-8] += error * 1 / 16;
                newImage[y+1][x-5] += error * 2 / 16;
                newImage[y+1][x+2] += error * 3 / 16;
                newImage[y+1][x+5] += error * 2 / 16;
                newImage[y+1][x+8] += error * 1 / 16;
            }
        }
    }
}

template<class A>
void Dithering<A>::sierraLite()
{
    int oldPixel;
    int newPixel;
    int error;

    for (int y = 0; y < height-1; y++)
    {
        if (width == newImage.at(0).size()){
            for (int x = 1; x < width-1; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+1]   += error * 2 / 4;
                newImage[y+1][x-1] += error * 1 / 4;
                newImage[y+1][x]   += error * 1 / 4;
            }
        }
        else {
            for (int x = 3; x < width-3; x+=3)
            {
                //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+3]   += error * 2 / 4;
                newImage[y+1][x-3] += error * 1 / 4;
                newImage[y+1][x]   += error * 1 / 4;
                //Green pixel
                oldPixel = newImage[y][x+1];
                newPixel = round(oldPixel/max);
                newImage[y][x+1] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+4]   += error * 2 / 8;
                newImage[y+1][x-4] += error * 1 / 8;
                newImage[y+1][x+1] += error * 1 / 8;
                //Blue pixel
                oldPixel = newImage[y][x+2];
                newPixel = round(oldPixel/max);
                newImage[y][x+2] = newPixel;
                error = oldPixel - newPixel;
                newImage[y][x+5]   += error * 2 / 8;
                newImage[y+1][x-5] += error * 1 / 8;
                newImage[y+1][x+2] += error * 1 / 8;
            }
        }
    }
}

template<class A>
void Dithering<A>::ordered4x4BayerMatrix()
{
    unsigned int bayer4x4[4][4] ={{1, 9, 3, 11}, 
                                  {13, 5, 15, 7}, 
                                  {4, 12, 2, 10}, 
                                  {16, 8, 14, 6}};

    int pixel;
    int factor = 1;
    int offset = (16 * (16 / 2) - 0.5) / (16 * 16); 
    int r = max / factor;

    for (int y = 0; y < height; y++)
    {
        if (width == newImage.at(0).size()){
            for (int x = 0; x < width; x++)
            {
                pixel = newImage[y][x];
                pixel += r * (bayer4x4[x % 16][y % 16] - offset);
            }
        }
        else {
            for (int x = 0; x < width; x+=3)
            {
                //Red pixel
                pixel = newImage[y][x];
                pixel += r * (bayer4x4[x % 16][y % 16] - offset);
                //Green pixel
                pixel = newImage[y][x+1];
                pixel += r * (bayer4x4[x % 16][y % 16] - offset);
                //Green pixel
                pixel = newImage[y][x+2];
                pixel += r * (bayer4x4[x % 16][y % 16] - offset);
            }
        }
    }
}

template<class A>
void Dithering<A>::ordered8x8BayerMatrix()
{
    unsigned int bayer8x8[8][8] = {{0,  32, 8,  40, 2,  34, 10, 42},
                                   {48, 16, 56, 24, 50, 18, 58, 26},
                                   {12, 44, 4,  36, 14, 46, 6,  38},
                                   {60, 28, 52, 20, 62, 30, 54, 22},
                                   {3,  35, 11, 43, 1,  33, 9,  41}, 
                                   {51, 19, 59, 27, 49, 17, 57, 25},
                                   {15, 47, 7,  39, 13, 45, 5,  37},
                                   {63, 31, 55, 23, 61, 29, 53, 21}};
    
    int pixel;
    int factor = 1;
    int offset = (64 * (64 / 2) - 0.5) / (64 * 64); 
    int r = max / factor;

    for (int y = 0; y < height; y++)
    {
        if (width == newImage.at(0).size()){
            for (int x = 0; x < width; x++)
            {
                pixel = newImage[y][x];
                pixel += r * (bayer8x8[x % 64][y % 64] - offset);
            }
        }
        else {
            for (int x = 0; x < width; x+=3)
            {
                //Red pixel
                pixel = newImage[y][x];
                pixel += r * (bayer8x8[x % 64][y % 64] - offset);
                //Green pixel
                pixel = newImage[y][x+1];
                pixel += r * (bayer8x8[x % 64][y % 64] - offset);
                //Green pixel
                pixel = newImage[y][x+2];
                pixel += r * (bayer8x8[x % 64][y % 64] - offset);
            }
        }
    }
}

template class Dithering <Pbm>; 
template class Dithering <Pgm>; 
template class Dithering <Ppm>; 