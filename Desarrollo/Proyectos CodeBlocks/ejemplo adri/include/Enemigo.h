#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <irrlicht.h>
#include "driverChoice.h"
#include "../include/Time.h"
#include "../include/Fuzzy.h"
#include "../include/Muros.h"
#include <World.h>
#include <Player.h>

#define MOV_SPEED 10.0f;


using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;


class Enemigo
{
    public:
        Enemigo();
        virtual ~Enemigo();
        void setCuboEnemigo(core::vector3df);
        b2Body* getBody();
        void inicialiazar(int,int, scene::ISceneManager*, core::vector3df p);
        void inicialiazar2(scene::ISceneManager*);
        int getEstado();
        core::vector3df getPosicion();
        core::vector3df getPunto();
        void setPosicion(core::vector3df vec, core::vector3df prot);
        void setPunto(core::vector3df este);
        void setEstado(int este);
        float getSospecha();
        scene::IMeshSceneNode* getModelo();
        core::vector3df getCuboEnemigo();
        void sospechar(core::vector3df posicionProta);
        void curar(Enemigo aliado);
        int maquinaEstados();
        void update(core::vector3df, Time, Enemigo *aliados[3]);
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
        void atacar();
        bool comprobarPunto(b2Vec2);
        void quitarVida();
        void setDanyado(bool);
        bool getDanyado();
        bool getMuerto();
        void setMuro(Muros* murito, Player *prota);
        bool getMuro();
        class Muros* morito;

    protected:

    private:
        scene::IMesh *mura1;
        scene::IMeshSceneNode *modelo;
        b2Body *body2;
        float tam;
        float movx, movy;
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
        float rotacion;
        bool danyado;
        Player *player;

        b2RayCastInput input;
        b2RayCastOutput	output;

        Fuzzy logica;
        scene::ISceneManager* smgr1;
        class World* iworld;



};

#endif // PLAYER_H
