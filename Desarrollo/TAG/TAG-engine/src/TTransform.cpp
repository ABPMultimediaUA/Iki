#include "TTransform.h"
#include <iostream>
#include <GL/gl.h>

TTransform::TTransform()
{
    matriz = mat4(1.f);
}

TTransform::~TTransform()
{
    //dtor
}

void TTransform::identidad()
{
     matriz = mat4(1.f);
}

void TTransform::cargar(mat4 mat)
{
    matriz = mat;
}

void TTransform::trasponer()
{
    transpose(matriz);
}

void TTransform::trasladar(float x, float y, float z)
{
    matriz = translate(matriz, vec3(x, y, z));
}

void TTransform::rotar(float angulo, float x, float y, float z)
{
    matriz = rotate(matriz, angulo, vec3(x, y, z));
}

void TTransform::beginDraw()
{
    std::cout<<"apilando matriz"<<std::endl;
    glPushMatrix();

    std::cout<<"multiplicando la transformacion a la actual"<<std::endl;
    //????
}

void TTransform::endDraw()
{
    std::cout<<"desapilando matriz"<<std::endl;
    glPopMatrix();
}
