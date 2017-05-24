#include "TEntidad.h"

mat4 TEntidad::ms_gmatriz = mat4(1.f);
stack<mat4> TEntidad::pila;

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

