#include "TCamara.h"

TCamara::TCamara()
{
    esPerspectiva = false;
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
