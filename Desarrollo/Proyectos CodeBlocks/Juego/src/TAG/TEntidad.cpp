#include "TEntidad.h"

glm::mat4 TEntidad::ms_gmatriz= glm::mat4(1.f);
stack<glm::mat4> TEntidad::pila;


TEntidad::TEntidad()
{

}

TEntidad::~TEntidad()
{
    //dtor
}

void TEntidad::beginDraw()
{

}

void TEntidad::endDraw()
{

}

