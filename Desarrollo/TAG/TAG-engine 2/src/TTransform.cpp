#include "TTransform.h"

TTransform::TTransform()
{
    matriz = mat4(1.f);
/*
    TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;
    !!! BEWARE !!! This lines actually performs the scaling FIRST, and THEN the rotation,
    and THEN the translation. This is how matrix multiplication works.
*/
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
    matriz = rotate(matriz, (float) radians(angulo), vec3(x, y, z));
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

mat4 TTransform::GetModel() const
{
		glm::mat4 posMatrix = glm::translate(m_pos);

		glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1,0,0));
		glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0,1,0));
		glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0,0,1));

		glm::mat4 scaleMatrix = glm::scale(m_scale);

		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotMatrix * scaleMatrix;

}
