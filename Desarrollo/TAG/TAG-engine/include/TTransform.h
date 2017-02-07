#ifndef TTRANSFORM_H
#define TTRANSFORM_H

#include <TEntidad.h>
#include "TMatriz4x4.h"


class TTransform : public TEntidad
{
    public:
        TTransform();
        virtual ~TTransform();

        void identidad();
        void cargar(TMatriz4x4);
        void trasponer();
        void trasladar(float x, float y, float z);
        void rotar(float ang, float x, float y, float z);

        void beginDraw();
        void endDraw();

    protected:

    private:
        TMatriz4x4 matriz;
};

#endif // TTRANSFORM_H
