#ifndef TLINEA_H
#define TLINEA_H

#include "TVector.h"

class TLinea
{
    public:

        TLinea(TVector vec1, TVector vec2) : start(vec1), fin(vec2){}
        TLinea(float xa, float ya, float za, float xb, float yb, float zb) : start(TVector(xa,ya,za)), fin(TVector(xb,yb,zb)){}

        ~TLinea();

        TVector getStart(){ return start;}
        TVector getEnd()  { return fin;}

    protected:

    private:
        TVector start;
        TVector fin;
};

#endif // TLINEA_H
