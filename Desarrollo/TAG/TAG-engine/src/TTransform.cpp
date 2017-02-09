#include <iostream>

#include "TTransform.h"

TTransform::TTransform()
{
    //ctor
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

}

void TTransform::trasponer()
{

}

void TTransform::trasladar(float x, float y, float z)
{
//matriz. funcion de trasladar en este caso

}

void TTransform::rotar(float ang, float x, float y, float z)
{

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
