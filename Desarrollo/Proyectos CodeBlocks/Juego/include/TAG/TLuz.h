#ifndef TLUZ_H
#define TLUZ_H

#include <iostream>
#include <TAG/TEntidad.h>


class TLuz : public TEntidad
{
    public:
        TLuz();
        virtual ~TLuz();
        vec3 getPoscion(){return posicion;};
        vec3 getIntensidad(){return intensidad;};
        void setPosicion(vec3 pos);
        void setIntensidad(vec3 col);


        void beginDraw();
        void endDraw();

    protected:

    private:
        vec3 intensidad;
        vec3 posicion;
};

#endif // TLUZ_H
