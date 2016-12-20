#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <irrlicht.h>
#include "driverChoice.h"
#include "../include/Time.h"
#include "Fuzzy.h"


using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;


class Enemigo
{
    public:
        void inicialiazar(int,int, scene::ISceneManager*, core::vector3df p);
        int getEstado();
        core::vector3df getPosicion();
        core::vector3df getPunto();
        void setPosicion(core::vector3df este);
        void setPunto(core::vector3df este);
        void setEstado(int este);
        float getSospecha();
        scene::IMeshSceneNode* getModelo();
        core::vector3df getCuboEnemigo();
        void sospechar(core::vector3df posicionProta);
        void curar(Enemigo aliado);
        int maquinaEstados();
        void update(core::vector3df, core::vector3df, Time, Enemigo *aliados[3]);
        void inspeccionar();
        void patrullar();
        void vigilar();
        void perseguir();
        void pedirAyuda();
        void proteger();
        void matar();
        void escanear();
        void avisarCapsulas();
        float getVida();



    protected:

    private:

        int id;
        int estado; //0-> patrullar 1-> vigilar 2-> combate 3-> pedir ayuda 4-> huir 5-> perseguir 6-> atacar 7->inspeccionar 8->sospechar 9->muerto
        int direccion; //0-> arriba 1-> derecha 2-> abajo 3-> izquierda
        int tipo; //0-> guardia, 1-> dron, 2-> medico
        float vida;
        float distanciaPlayer;
        float sospecha;
        float tiempoVigilando;
        int tiempoEscaneando;
        core::vector3df posicion;
        core::vector3df posicionInicial;
        core::vector3df puntoInteres;
        scene::IMeshSceneNode *modelo;
        core::vector3df cuboEnemigo;
        core::vector3df direccionHaciaProta;
        core::vector3df posicionAliado;
        core::vector3df direccionHaciaAliado;
        core::vector3df posicionProta;
        f32 avMovement;
        Time tiempo;
        float time;
        float reloj;
        bool primeraVez;
        bool mensajePendiente;
        int mensajeEstado;
        Enemigo *compis[3];
        bool muerto;
        bool hayAliado;

        Fuzzy logica;

};

#endif // ENEMIGO_H

