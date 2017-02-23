#include "TCamara.h"


TCamara::TCamara(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
{
    m_perspective = glm::perspective(fov, aspect, zNear, zFar);
    m_position = pos;
    m_forward = glm::vec3(0,0,1);
    m_up = glm::vec3(0,1,0);
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
void TCamara::beginDraw()
{

}
void TCamara::endDraw()
{

}
