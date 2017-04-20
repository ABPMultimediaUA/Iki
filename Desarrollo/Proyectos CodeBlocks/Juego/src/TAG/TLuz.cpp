#include "TAG/TLuz.h"

TLuz::TLuz()
{
    posicion= vec3(0.0f, 0.0f, 0.0f);
    intensidad= vec3(0.0f, 0.0f, 0.0f);
}

TLuz::~TLuz()
{
    //dtor
}

void TLuz::setIntensidad(vec3 col)
{
    intensidad = col;
}

void TLuz::setPosicion(vec3 pos)
{
    posicion = pos;
}

void TLuz::beginDraw()
{
  //  std::cout << "  Luz detected " << std::endl;
}

void TLuz::endDraw()
{

}
