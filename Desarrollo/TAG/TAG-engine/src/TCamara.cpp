#include "TCamara.h"

TCamara::TCamara()
{
    esPerspectiva= false;
}

TCamara::~TCamara()
{
    //dtor
}

void TCamara::setPerspectiva(float sup, float inf, float izq, float dch, float cer, float lej)
{
    superior= sup;
    inferior= inf;
    izquierda= izq;
    derecha= dch;
    cercano= cer;
    lejano= lej;

    esPerspectiva= true;
}
void TCamara::setParalela(float sup, float inf, float izq, float dch, float cer, float lej)
{
    superior= sup;
    inferior= inf;
    izquierda= izq;
    derecha= dch;
    cercano= cer;
    lejano= lej;

    esPerspectiva= false;
}
void TCamara::beginDraw()
{
    std::cout << "camara draw()" <<std::endl;
}
void TCamara::endDraw()
{
    //cout << "Desapilamos camara" << endl;
}
