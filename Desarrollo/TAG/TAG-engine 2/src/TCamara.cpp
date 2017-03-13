#include "TCamara.h"

TCamara::TCamara(const vec3& pos, float fov, float aspect, float cer, float lej)
{
    m_perspective = glm::perspective(fov, aspect, cer, lej);
    m_position = pos;
    //esPerspectiva = false;
}


TCamara::~TCamara()
{
    //dtor
}

void TCamara::setPerspectiva(float sup, float inf, float izq, float dch, float cer, float lej)
{
    superior  = sup;
    inferior  = inf;
    izquierda = izq;
    derecha   = dch;
    cercano   = cer;
    lejano    = lej;

    esPerspectiva = true;

}
void TCamara::setParalela(float sup, float inf, float izq, float dch, float cer, float lej)
{
    superior  = sup;
    inferior  = inf;
    izquierda = izq;
    derecha   = dch;
    cercano   = cer;
    lejano    = lej;

    esPerspectiva = false;
}

mat4 TCamara::getViewProjection() const
{
    return m_perspective * lookAt(m_position, m_position + vec3(0,0,1), vec3(0,1,0));
}


void TCamara::beginDraw()
{

}
void TCamara::endDraw()
{

}
