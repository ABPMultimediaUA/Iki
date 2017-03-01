#include "TTransform.h"

/*TTransform::TTransform()
{
    matriz = mat4(1.f);

    TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;
    !!! BEWARE !!! This lines actually performs the scaling FIRST, and THEN the rotation,
    and THEN the translation. This is how matrix multiplication works.

}*/

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
    pila.push(ms_gmatriz);
    std::cout<<"apilando matriz"<<std::endl;

    ms_gmatriz= ms_gmatriz * matriz;
    std::cout<<"multiplicando la transformacion a la actual"<<std::endl;
}

void TTransform::endDraw()
{
    ms_gmatriz= pila.top();
    pila.pop();
    std::cout<<"desapilando matriz"<<std::endl;
}
