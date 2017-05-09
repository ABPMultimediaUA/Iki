#ifndef TLINEA_H
#define TLINEA_H

#include "TVector.h"

class TLinea
{
    public:
        TLinea(T xa, T ya, T za, T xb, T yb, T zb);
        TLinea(TVector, TVector);
        ~TLinea();

        TVector getStart(){ return start;}
        TVector getEnd()  { return fin;}

    protected:

    private:
        TVector start;
        TVector fin;
};

#endif // TLINEA_H
