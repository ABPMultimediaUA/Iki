#include "TLuz.h"

TLuz::TLuz(/*const glm::vec3& intensity*/)
{

    //intensidad= intensity;
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

/*void TLuz::Intensidad()
{
    //TShader::getShader() programLightingMap

}
*/
void TLuz::beginDraw()
{


}

void TLuz::endDraw()
{

}
