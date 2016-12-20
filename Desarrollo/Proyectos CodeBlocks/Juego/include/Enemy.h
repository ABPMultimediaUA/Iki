#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;


class Enemy
{
    public:
        void inicialiazar(int, scene::ISceneManager*, core::vector3df p);
        int getEstado();
        core::vector3df getPosicion();
        core::vector3df getPunto();
        void setPosicion(core::vector3df este);
        void setPunto(core::vector3df este);
        float getSospecha();
        scene::IMeshSceneNode* getModelo();
        core::vector3df getCuboEnemigo();
        void patrullar();
        void sospechar(core::vector3df posicionProta);
        void atacar(core::vector3df posicionProta);
        int maquinaEstados(core::vector3df posicionProta);
        void update(core::vector3df, core::vector3df, f32);

    protected:

    private:

        int estado; //0-> patrulla, 1-> sospechar, 2-> atacar, 3-> nsnc
        int direccion; //0-> arriba, 1-> derecha, 2-> abajo, 3-> izquierda
        int tipo; //0-> guardia, 1-> dron, 2-> medico
        float sospecha;
        core::vector3df posicion;
        core::vector3df posicionInicial;
        core::vector3df puntoInteres;
        scene::IMeshSceneNode *modelo;
        core::vector3df cuboEnemigo;

};

#endif // ENEMIGO_H

