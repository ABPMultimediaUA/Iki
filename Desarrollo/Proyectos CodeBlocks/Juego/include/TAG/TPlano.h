#ifndef TPLANO_H
#define TPLANO_H

#include "TVector.h"

class TPlano
{
    public:
        TPlano() : Normal(0,1,0) {recalculateD(TVector(0,0,0));}
        TPlano(const TVector& MPoint, const TVector& Normal) : Normal(Normal) { recalculateD(MPoint); }
        TPlano(float px, float py, float pz, float nx, float ny, float nz) : Normal(nx, ny, nz) { recalculateD(TVector(px, py, pz)); }
        ~TPlano();

        void recalculateD(const TVector&);
        bool getIntersectionWithLine(const TVector&, const TVector&, TVector&);

    protected:

    private:
        TVector Normal;
        float Distance; ///Distancia desde el origen
};

#endif // TPLANO_H
