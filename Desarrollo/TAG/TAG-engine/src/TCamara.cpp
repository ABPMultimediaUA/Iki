#include "TCamara.h"

TCamara::TCamara(const vec3& pos, float grad, int anch, int alt, float cer, float lej)
{
    cercano   = cer;
    lejano    = lej;
    v_posicion = pos;

    ancho = anch;
    alto = alt; //comprobar

    viewpoint= ancho/alto;

    m_perspectiva= perspective((float) radians(grad), viewpoint, cer, lej);

    esPerspectiva = true;
}

TCamara::~TCamara()
{
    //dtor
}

void TCamara::setPerspectiva(float grad, int anch, int alt, float cer, float lej)
{
    cercano   = cer;
    lejano    = lej;
    ancho = anch;
    alto = alt; //comprobar

    viewpoint= ancho/alto;

    m_perspectiva= perspective((float) radians(grad), viewpoint, cer, lej);

    esPerspectiva = true;
}
void TCamara::setParalela(float izq, float dch, float inf, float sup, float cer, float lej)
{


    m_paralela= ortho(izq, dch, inf, sup, cer, lej);

    esPerspectiva = false;
}

mat4 TCamara::getMatrizProyeccion() const
{
    if(esPerspectiva)
        return m_perspectiva;
    else
        return m_paralela;
}

void TCamara::beginDraw()
{
    std::cout << "  Camara detected " << std::endl;
}
void TCamara::endDraw()
{

}
