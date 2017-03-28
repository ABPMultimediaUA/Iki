#include "TAnimacion.h"

TAnimacion::TAnimacion()
{
    //ctor
}

TAnimacion::~TAnimacion()
{
    //dtor
}

void TAnimacion::almacenarMalla(TRecursoMalla* malla)
{
    animacion.push_back(malla);
}

void TAnimacion::beginDraw(int frame)
{
    animacion[frame]->draw();
}

void TAnimacion::endDraw()
{

}
