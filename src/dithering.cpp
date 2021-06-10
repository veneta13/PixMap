#include "../inc/dithering.h"

template<class A>
Dithering<A>::Dithering (const Dithering<A> &p)
{
    height = p.height;
    width = p.width;
    max = 1;

    std::vector<int> line;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            line.push_back(p.imageGrid.at(i*width + j));
        }
        newImage.push_back(line);
        line.clear();
    }
}

template<class A>
void Dithering<A>::floydSteinberg()
{
    int oldPixel;
    int newPixel;
    int error;

    for (int y = 0; y < height-1; y++)
    {
        for (int x = 1; x < width-1; x++)
        {
            oldPixel = newImage[y][x];
            newPixel = std::round(oldPixel/max);
            newImage[y][x] = newPixel;
            error = oldPixel - newPixel;
            newImage[y][x+1]   +=  error * 7 / 16;
            newImage[y+1][x-1] += error * 3 / 16;
            newImage[y+1][x]   +=  + error * 5 / 16;
            newImage[y+1][x+1] += error * 1 / 16;
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
        for (int x = 0; x < width-1; x++)
        {
            oldPixel = newImage[y][x];
            newPixel = std::round(oldPixel/max);
            newImage[y][x] = newPixel;
            error = oldPixel - newPixel;
            newImage[y][x+1]   +=  error * 3 / 8;
            newImage[y+1][x]   +=  + error * 3 / 8;
            newImage[y+1][x+1] += error * 2 / 8;
        }
    }
}

template<class A>
void Dithering<A>::jarvisJudiceNinke()
{

}

template<class A>
void Dithering<A>::stucki()
{

}

template<class A>
void Dithering<A>::atkinson()
{

}

template<class A>
void Dithering<A>::burkes()
{

}

template<class A>
void Dithering<A>::sierra()
{

}

template<class A>
void Dithering<A>::twoRowSierra()
{

}

template<class A>
void Dithering<A>::sierraLite()
{
    
}

template<class A>
void Dithering<A>::ordered4x4BayerMatrix()
{

}

template<class A>
void Dithering<A>::ordered8x8BayerMatrix()
{

}
