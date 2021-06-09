#include "../inc/dithering.h"

Dithering::Dithering (Pbm * p)
    : height (p->height), width (p->width), max (1){}

Dithering::Dithering (Pgm * p)
    : height (p->height), width (p->width), max (p->max){}

Dithering::Dithering (Ppm * p)
    : height (p->height), width (p->width), max (p->max){}

void Dithering::floydSteinberg()
{

}

void Dithering::falseFloydSteinberg()
{

}

void Dithering::jarvisJudiceNinke()
{

}

void Dithering::stucki()
{

}

void Dithering::atkinson()
{

}

void Dithering::burkes()
{

}

void Dithering::sierra()
{

}

void Dithering::twoRowSierra()
{

}

void Dithering::sierraLite()
{
    
}

void Dithering::ordered4x4BayerMatrix()
{

}

void Dithering::ordered8x8BayerMatrix()
{

}
