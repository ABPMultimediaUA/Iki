#include "TLinea.h"

TLinea::TLinea(T xa, T ya, T za, T xb, T yb, T zb)
{
    start(xa, ya, za);
    fin(xb, yb, zb);
}

TLinea::TLinea(TVector vec1, TVector vec2)
{
    start = vec1;
    fin = vec2;
}

TLinea::~TLinea()
{
    //dtor
}
