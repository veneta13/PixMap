#include "../inc/dithering.h"

template<class A>
Dithering<A>::Dithering (int height, int width, int man, std::vector<int> imageGrid)
{
    //copy the information from the image to Dithering object
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
                //if the image is PPM copy all colors
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
    //choose dither type
        if (type == 1){
            floydSteinberg();
        }
        else if (type == 2){
            falseFloydSteinberg();
        }
        else if (type == 3){
            jarvisJudiceNinke();
        }
        else if (type == 4){
            stucki();
        }
        else if (type == 5){
            atkinson();
        }
        else if (type == 6){
            burkes();
        }
        else if (type == 7){
            sierra();
        }
        else if (type == 8){
            twoRowSierra();
        }
        else if (type == 9){
            sierraLite();
        }
        else if (type == 10){
            ordered4x4BayerMatrix();
        }
        else if (type == 11){
            ordered8x8BayerMatrix();
        }
        else {
            throw std::runtime_error("Error: Unknown dither type.");
        }
}

template<class A>
std::vector<std::vector<int>> Dithering<A>::returnImage()
{
    //return dithered image
    return newImage;
}

template<class A>
void Dithering<A>::floydSteinberg()
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

    for (int y = 0; y < height-1; y++)
    {
        if (width == newImage.at(0).size()){
            //dithering for PBM and PGM images
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
            //dithering for PPM images
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
     /*
    Dither according to the False Floyd-Steinberg matrix:
        X   3
        3   2
        (1/8)
    */

    int oldPixel; //old pixel value
    int newPixel; //new pixel value
    int error; //error value

    for (int y = 0; y < height-1; y++)
    {
        if (width == newImage.at(0).size()){
            //dithering for PBM and PGM images
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
            //dithering for PPM images
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

    for (int y = 0; y < height-2; y++)
    {
        if (width == newImage.at(0).size()){
            //dithering for PBM and PGM images
            for (int x = 2; x < width-2; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+1]   += error * 7 / 48;
                newImage[y][x+2]   += error * 5 / 48;
                //second row
                newImage[y+1][x-2] += error * 3 / 48;
                newImage[y+1][x-1] += error * 5 / 48;
                newImage[y+1][x]   += error * 7 / 48;
                newImage[y+1][x+1] += error * 5 / 48;
                newImage[y+1][x+2] += error * 3 / 48;
                //third row
                newImage[y+2][x-2] += error * 1 / 48;
                newImage[y+2][x-1] += error * 3 / 48;
                newImage[y+2][x]   += error * 5 / 48;
                newImage[y+2][x+1] += error * 3 / 48;
                newImage[y+2][x+2] += error * 1 / 48;
            }
        }
        else {
            //dithering for PPM images
            for (int x = 6; x < width-6; x+=3)
            {
            //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+3]   += error * 7 / 48;
                newImage[y][x+6]   += error * 5 / 48;
                //second row
                newImage[y+1][x-6] += error * 3 / 48;
                newImage[y+1][x-3] += error * 5 / 48;
                newImage[y+1][x]   += error * 7 / 48;
                newImage[y+1][x+3] += error * 5 / 48;
                newImage[y+1][x+6] += error * 3 / 48;
                //third row
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
                //first row
                newImage[y][x+4]   += error * 7 / 48;
                newImage[y][x+7]   += error * 5 / 48;
                //second row
                newImage[y+1][x-7] += error * 3 / 48;
                newImage[y+1][x-4] += error * 5 / 48;
                newImage[y+1][x+1] += error * 7 / 48;
                newImage[y+1][x+4] += error * 5 / 48;
                newImage[y+1][x+7] += error * 3 / 48;
                //third row
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
                //first row
                newImage[y][x+5]   += error * 7 / 48;
                newImage[y][x+8]   += error * 5 / 48;
                //second row
                newImage[y+1][x-8] += error * 3 / 48;
                newImage[y+1][x-5] += error * 5 / 48;
                newImage[y+1][x+2] += error * 7 / 48;
                newImage[y+1][x+5] += error * 5 / 48;
                newImage[y+1][x+8] += error * 3 / 48;
                //third row
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

    for (int y = 0; y < height-2; y++)
    {
        if (width == newImage.at(0).size()){
            //dithering for PBM and PGM images
            for (int x = 2; x < width-2; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+1]   += error * 8 / 42;
                newImage[y][x+2]   += error * 4 / 42;
                //second row
                newImage[y+1][x-2] += error * 2 / 42;
                newImage[y+1][x-1] += error * 4 / 42;
                newImage[y+1][x]   += error * 8 / 42;
                newImage[y+1][x+1] += error * 4 / 42;
                newImage[y+1][x+2] += error * 2 / 42;
                //third row
                newImage[y+2][x-2] += error * 1 / 42;
                newImage[y+2][x-1] += error * 2 / 42;
                newImage[y+2][x]   += error * 4 / 42;
                newImage[y+2][x+1] += error * 2 / 42;
                newImage[y+2][x+2] += error * 1 / 42;
            }
        }
        else {
            //dithering for PPM images
            for (int x = 6; x < width-6; x+=3)
            {
            //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+3]   += error * 8 / 42;
                newImage[y][x+6]   += error * 4 / 42;
                //second row
                newImage[y+1][x-6] += error * 2 / 42;
                newImage[y+1][x-3] += error * 4 / 42;
                newImage[y+1][x]   += error * 8 / 42;
                newImage[y+1][x+3] += error * 4 / 42;
                newImage[y+1][x+6] += error * 2 / 42;
                //third row
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
                //first row
                newImage[y][x+4]   += error * 8 / 42;
                newImage[y][x+7]   += error * 4 / 42;
                //second row
                newImage[y+1][x-7] += error * 2 / 42;
                newImage[y+1][x-4] += error * 4 / 42;
                newImage[y+1][x+1] += error * 8 / 42;
                newImage[y+1][x+4] += error * 4 / 42;
                newImage[y+1][x+7] += error * 2 / 42;
                //third row
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
                //first row
                newImage[y][x+5]   += error * 8 / 42;
                newImage[y][x+8]   += error * 4 / 42;
                //second row
                newImage[y+1][x-8] += error * 2 / 42;
                newImage[y+1][x-5] += error * 4 / 42;
                newImage[y+1][x+2] += error * 8 / 42;
                newImage[y+1][x+5] += error * 4 / 42;
                newImage[y+1][x+8] += error * 2 / 42;
                //third row
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

    for (int y = 0; y < height-2; y++)
    {
        if (width == newImage.at(0).size()){
            //dithering for PBM and PGM images
            for (int x = 0; x < width-2; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+1]   += error / 8;
                newImage[y][x+2]   += error / 8;
                //second row
                newImage[y+1][x-1] += error / 8;
                newImage[y+1][x]   += error / 8;
                newImage[y+1][x+1] += error / 8;
                //third row
                newImage[y+2][x]   += error / 8;
            }
        }
        else {
            //dithering for PPM images
            for (int x = 3; x < width-6; x+=3)
            {
            //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+3]   += error / 8;
                newImage[y][x+6]   += error / 8;
                //second row
                newImage[y+1][x-3] += error / 8;
                newImage[y+1][x]   += error / 8;
                newImage[y+1][x+3] += error / 8;
                //third row
                newImage[y+2][x]   += error / 8;
            //Green pixel
                oldPixel = newImage[y][x+1];
                newPixel = round(oldPixel/max);
                newImage[y][x+1] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+4]   += error / 8;
                newImage[y][x+7]   += error / 8;
                //second row
                newImage[y+1][x-4] += error / 8;
                newImage[y+1][x+1] += error / 8;
                newImage[y+1][x+4] += error / 8;
                //third row
                newImage[y+2][x+1] += error / 8;
            //Blue pixel
                oldPixel = newImage[y][x+2];
                newPixel = round(oldPixel/max);
                newImage[y][x+2] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+5]   += error / 8;
                newImage[y][x+8]   += error / 8;
                //second row
                newImage[y+1][x-5] += error / 8;
                newImage[y+1][x+2] += error / 8;
                newImage[y+1][x+5] += error / 8;
                //third row
                newImage[y+2][x+2] += error / 8;
            }
        }
    }
}

template<class A>
void Dithering<A>::burkes()
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

    for (int y = 0; y < height-1; y++)
    {
        if (width == newImage.at(0).size()){
            //dithering for PBM and PGM images
            for (int x = 2; x < width-2; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+1]   += error * 8 / 32;
                newImage[y][x+2]   += error * 4 / 32;
                //second row
                newImage[y+1][x-2] += error * 2 / 32;
                newImage[y+1][x-1] += error * 4 / 32;
                newImage[y+1][x]   += error * 8 / 32;
                newImage[y+1][x+1] += error * 4 / 32;
                newImage[y+1][x+2] += error * 2 / 32;
            }
        }
        else {
            //dithering for PPM images
            for (int x = 6; x < width-6; x+=3)
            {
            //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+3]   += error * 8 / 32;
                newImage[y][x+6]   += error * 4 / 32;
                //second row
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
                //first row
                newImage[y][x+4]   += error * 8 / 32;
                newImage[y][x+7]   += error * 4 / 32;
                //second row
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
                //first row
                newImage[y][x+5]   += error * 8 / 32;
                newImage[y][x+8]   += error * 4 / 32;
                //second row
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

    for (int y = 0; y < height-2; y++)
    {
        if (width == newImage.at(0).size()){
            //dithering for PBM and PGM images
            for (int x = 2; x < width-2; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+1]   += error * 5 / 32;
                newImage[y][x+2]   += error * 3 / 32;
                //second row
                newImage[y+1][x-2] += error * 2 / 32;
                newImage[y+1][x-1] += error * 4 / 32;
                newImage[y+1][x]   += error * 5 / 32;
                newImage[y+1][x+1] += error * 4 / 32;
                newImage[y+1][x+2] += error * 2 / 32;
                //third row
                newImage[y+2][x-1] += error * 2 / 32;
                newImage[y+2][x]   += error * 3 / 32;
                newImage[y+2][x+1] += error * 2 / 32;
                
            }
        }
        else {
            //dithering for PPM images
            for (int x = 6; x < width-6; x+=3)
            {
            //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+3]   += error * 5 / 42;
                newImage[y][x+6]   += error * 3 / 42;
                //second row
                newImage[y+1][x-6] += error * 2 / 42;
                newImage[y+1][x-3] += error * 4 / 42;
                newImage[y+1][x]   += error * 5 / 42;
                newImage[y+1][x+3] += error * 4 / 42;
                newImage[y+1][x+6] += error * 2 / 42;
                //third row
                newImage[y+2][x-3] += error * 2 / 42;
                newImage[y+2][x]   += error * 3 / 42;
                newImage[y+2][x+3] += error * 2 / 42;
            //Green pixel
                oldPixel = newImage[y][x+1];
                newPixel = round(oldPixel/max);
                newImage[y][x+1] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+4]   += error * 5 / 42;
                newImage[y][x+7]   += error * 3 / 42;
                //second row
                newImage[y+1][x-7] += error * 2 / 42;
                newImage[y+1][x-4] += error * 4 / 42;
                newImage[y+1][x+1] += error * 5 / 42;
                newImage[y+1][x+4] += error * 4 / 42;
                newImage[y+1][x+7] += error * 2 / 42;
                //third row
                newImage[y+2][x-4] += error * 2 / 42;
                newImage[y+2][x+1] += error * 3 / 42;
                newImage[y+2][x+4] += error * 2 / 42;
            //Blue pixel
                oldPixel = newImage[y][x+2];
                newPixel = round(oldPixel/max);
                newImage[y][x+2] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+5]   += error * 5 / 42;
                newImage[y][x+8]   += error * 3 / 42;
                //second row
                newImage[y+1][x-8] += error * 2 / 42;
                newImage[y+1][x-5] += error * 4 / 42;
                newImage[y+1][x+2] += error * 5 / 42;
                newImage[y+1][x+5] += error * 4 / 42;
                newImage[y+1][x+8] += error * 2 / 42;
                //third row
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
    /*
    Dither according to the Two-Row Sierra matrix:
            X   4   3
    1   2   3   2   1
          (1/16)
    */
    int oldPixel; //old pixel value
    int newPixel; //new pixel value
    int error; //error value

    for (int y = 0; y < height-1; y++)
    {
        if (width == newImage.at(0).size()){
            //dithering for PBM and PGM images
            for (int x = 2; x < width-2; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+1]   += error * 4 / 16;
                newImage[y][x+2]   += error * 3 / 16;
                //second row
                newImage[y+1][x-2] += error * 1 / 16;
                newImage[y+1][x-1] += error * 2 / 16;
                newImage[y+1][x]   += error * 3 / 16;
                newImage[y+1][x+1] += error * 2 / 16;
                newImage[y+1][x+2] += error * 1 / 16;
            }
        }
        else {
            //dithering for PPM images
            for (int x = 6; x < width-6; x+=3)
            {
            //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+3]   += error * 4 / 16;
                newImage[y][x+6]   += error * 3 / 16;
                //second row
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
                //first row
                newImage[y][x+4]   += error * 4 / 16;
                newImage[y][x+7]   += error * 3 / 16;
                //second row
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
                //first row
                newImage[y][x+5]   += error * 4 / 16;
                newImage[y][x+8]   += error * 3 / 16;
                //second row
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
    /*
    Dither according to the Sierra Lite matrix:
            X   2
        1   1
          (1/4)
    */
    int oldPixel; //old pixel value
    int newPixel; //new pixel value
    int error; //error value

    for (int y = 0; y < height-1; y++)
    {
        if (width == newImage.at(0).size()){
            //dithering for PBM and PGM images
            for (int x = 1; x < width-1; x++)
            {
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+1]   += error * 2 / 4;
                //second row
                newImage[y+1][x-1] += error * 1 / 4;
                newImage[y+1][x]   += error * 1 / 4;
            }
        }
        else {
            //dithering for PPM images
            for (int x = 3; x < width-3; x+=3)
            {
            //Red pixel
                oldPixel = newImage[y][x];
                newPixel = round(oldPixel/max);
                newImage[y][x] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+3]   += error * 2 / 4;
                //second row
                newImage[y+1][x-3] += error * 1 / 4;
                newImage[y+1][x]   += error * 1 / 4;
            //Green pixel
                oldPixel = newImage[y][x+1];
                newPixel = round(oldPixel/max);
                newImage[y][x+1] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+4]   += error * 2 / 8;
                //second row
                newImage[y+1][x-4] += error * 1 / 8;
                newImage[y+1][x+1] += error * 1 / 8;
            //Blue pixel
                oldPixel = newImage[y][x+2];
                newPixel = round(oldPixel/max);
                newImage[y][x+2] = newPixel;
                error = oldPixel - newPixel;
                //first row
                newImage[y][x+5]   += error * 2 / 8;
                //second row
                newImage[y+1][x-5] += error * 1 / 8;
                newImage[y+1][x+2] += error * 1 / 8;
            }
        }
    }
}

template<class A>
void Dithering<A>::ordered4x4BayerMatrix()
{
    //dithering according to the Bayer 4x4 matrix
    unsigned int bayer4x4[4][4] ={{1, 9, 3, 11}, 
                                  {13, 5, 15, 7}, 
                                  {4, 12, 2, 10}, 
                                  {16, 8, 14, 6}};

    int pixel; //current pixel
    int factor = 16;
    int offset = (16 * (16 / 2) - 0.5) / (16 * 16); //calculate offset
    int error = max / factor; //error value

    for (int y = 0; y < height; y++)
    {
        if (width == newImage.at(0).size()){
            //dithering for PBM and PGM images
            for (int x = 0; x < width; x++)
            {
                pixel = newImage[y][x];
                pixel += error * (bayer4x4[x % 16][y % 16] - offset);
            }
        }
        else {
            //dithering for PPM images
            for (int x = 0; x < width; x+=3)
            {
                //Red pixel
                pixel = newImage[y][x];
                pixel += error * (bayer4x4[x % 16][y % 16] - offset);
                //Green pixel
                pixel = newImage[y][x+1];
                pixel += error * (bayer4x4[x % 16][y % 16] - offset);
                //Green pixel
                pixel = newImage[y][x+2];
                pixel += error * (bayer4x4[x % 16][y % 16] - offset);
            }
        }
    }
}

template<class A>
void Dithering<A>::ordered8x8BayerMatrix()
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
    
    int pixel; //current pixel
    int factor = 64;
    int offset = (64 * (64 / 2) - 0.5) / (64 * 64); //calculate offset
    int error = max / factor; //calculate error

    for (int y = 0; y < height; y++)
    {
        if (width == newImage.at(0).size()){
            //dithering for PBM and PGM images
            for (int x = 0; x < width; x++)
            {
                pixel = newImage[y][x];
                pixel += error * (bayer8x8[x % 64][y % 64] - offset);
            }
        }
        else {
            //dithering for PPM images
            for (int x = 0; x < width; x+=3)
            {
                //Red pixel
                pixel = newImage[y][x];
                pixel += error * (bayer8x8[x % 64][y % 64] - offset);
                //Green pixel
                pixel = newImage[y][x+1];
                pixel += error * (bayer8x8[x % 64][y % 64] - offset);
                //Green pixel
                pixel = newImage[y][x+2];
                pixel += error * (bayer8x8[x % 64][y % 64] - offset);
            }
        }
    }
}

//templates for allowed classes
template class Dithering <Pbm>; 
template class Dithering <Pgm>; 
template class Dithering <Ppm>; 