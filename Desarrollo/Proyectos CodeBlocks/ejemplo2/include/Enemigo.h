#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <irrlicht.h>
#include "driverChoice.h"
#include "../include/Time.h"


using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;


class Enemigo
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
        void sospechar(core::vector3df posicionProta);
        void curar(Enemigo aliado);
        int maquinaEstados();
        void update(core::vector3df, core::vector3df, Time);
        void inspeccionar();
        void patrullar();
        void vigilar();


    protected:

    private:

        int estado; //0-> patrullar 1-> vigilar 2-> combate 3-> pedir ayuda 4-> huir 5-> perseguir 6-> atacar 7->inspeccionar 8->sospechar 9->muerto
        int direccion; //0-> arriba 1-> derecha 2-> abajo 3-> izquierda
        int tipo; //0-> guardia, 1-> dron, 2-> medico
        float distanciaPlayer;
        float sospecha;
        float tiempoVigilando;
        core::vector3df posicion;
        core::vector3df posicionInicial;
        core::vector3df puntoInteres;
        scene::IMeshSceneNode *modelo;
        core::vector3df cuboEnemigo;
        core::vector3df direccionHaciaProta;
        f32 avMovement;
        Time tiempo;
        float time;

};

#endif // ENEMIGO_H

