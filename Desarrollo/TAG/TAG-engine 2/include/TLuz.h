#ifndef TLUZ_H
#define TLUZ_H

#include <iostream>
#include <TEntidad.h>
#include "TColor.h"


class TLuz : public TEntidad
{
    public:
        TLuz();
        virtual ~TLuz();

        void setIntensidad(TColor col);
        TColor getIntensidad();

        void beginDraw();
        void endDraw();

    protected:

    private:
        TColor intensidad;
};

#endif // TLUZ_H
