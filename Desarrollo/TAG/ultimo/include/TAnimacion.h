#ifndef TANIMACION_H
#define TANIMACION_H

#include <TEntidad.h>
#include "TMalla.h"
#include <iostream>



class TAnimacion : public TEntidad
{
    public:
        TAnimacion(const unsigned int& length);
        virtual ~TAnimacion();

        void cargarAnimacion(const std::string& fileName);

        void beginDraw();
        void endDraw();

    protected:

    private:
        TMalla* animacion[200];
        unsigned int frames = 0;
        unsigned int m_longitud;
};

#endif // TANIMACION_H
