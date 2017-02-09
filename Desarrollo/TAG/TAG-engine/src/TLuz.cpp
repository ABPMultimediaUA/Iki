#include "TLuz.h"

TLuz::TLuz()
{

}

TLuz::~TLuz()
{
    //dtor
}

void TLuz::setIntensidad(TColor col)
{
    intensidad= col;
}
TColor TLuz::getIntensidad()
{
    return intensidad;
}
void TLuz::beginDraw()
{

}
void TLuz::endDraw()
{

}
