#include <iostream>

#include "TTransform.h"

TTransform::TTransform()
{
    matriz= mat4(1.f);
}

TTransform::~TTransform()
{
    //dtor
}

void TTransform::identidad()
{

}

void TTransform::cargar(mat4 mat)
{
    //no estoy seguro de esta comprobacion
    if(mat != mat4(1.f))
    {
        matriz= mat;
    }
}

void TTransform::trasponer()
{
    transpose(matriz);
}

void TTransform::trasladar(float x, float y, float z)
{
    matriz= translate(mat4(1.f), vec3(x, y, z));
}

void TTransform::rotar(float orient, float x, float y, float z)
{
    matriz= rotate(matriz, orient, vec3(x, y, z));
}

void TTransform::beginDraw()
{
    std::cout<<"apilando matriz"<<std::endl;
    std::cout<<"multiplicando la matriz a la matriz actual"<<std::endl;
}

void TTransform::endDraw()
{
    std::cout<<"desapilando matriz"<<std::endl;
}
