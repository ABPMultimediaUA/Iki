#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <irrlicht.h>
#include "driverChoice.h"


class Enemigo
{
    public:
        void inicialiazar();
        int getEstado();
        core::vector3df getPosicion();
        core::vector3df getPunto();
        void setPosicion(core::vector3df este);
        void setPunto(core::vector3df este);
        float getSospecha();
        void patrullar();
        void sospecha(core::vector3df posicionProta);
        void atacar(core::vector3df posicionProta);

    protected:

    private:

        int estado; //0-> patrulla, 1-> sospechar, 2-> atacar, 3-> nsnc
        int tipo; //0-> guardia, 1-> dron, 2-> medico
        float sospecha;
        core::vector3df posicion;
        core::vector3df puntoInteres;

};

#endif // ENEMIGO_H
