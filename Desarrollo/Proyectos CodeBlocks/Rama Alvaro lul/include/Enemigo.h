#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <irrlicht.h>
#include "driverChoice.h"
#include "../include/Time.h"
#include "../include/Fuzzy.h"
#include <World.h>
#include <Player.h>
#include "../include/Map.h"

#include "../include/PatrolRoute.h"

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
        void inicialiazar(int,int, scene::ISceneManager*, core::vector3df p, PatrolRoute pr);
        void inicialiazar2(scene::ISceneManager*, core::vector3df p);
        int getEstado();
        core::vector3df getPosicion();
        core::vector3df getPunto();
        void setPosicion();
        void setPunto(core::vector3df este);
        void setEstado(int este);
        float getSospecha();
        scene::IMeshSceneNode* getModelo();
        core::vector3df getCuboEnemigo();
        void sospechar(core::vector3df posicionProta);
        void curar(Enemigo aliado);
        int maquinaEstados();
        void update(core::vector3df, Time, Enemigo *aliados[7]);
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
        void setMuro(Map* murito, Player *prota);
        bool noteveo();
        bool getCreado();
        bool seeWhereIgo();
        class Map* morito;
        void huir();
        int getTipo();
        int getID();
        int i=0;
        float distanciaPlayer;
        float angulo;
        float angulo7;

    protected:

    private:
        scene::IMesh *mura1;
        scene::IMeshSceneNode *modelo;
        scene::IMeshSceneNode *modelo2;

        float angulohuhu = 0;
        float distanciahuhu = 0;
        scene::IMesh *rayo;
        bool prepara = false;
        bool solounaveh = false;


        b2Body *body2;
        b2Vec2 bodyauxiliar;
        float tam;
        float movx, movy;
        int id;
        int estado; //0-> patrullar 1-> vigilar 2-> combate 3-> pedir ayuda 4-> huir 5-> perseguir 6-> atacar 7->inspeccionar 8->sospechar 9->muerto
        int tipo; //0-> guardia, 1-> dron, 2-> medico
        float vida;
        float sospecha;
        float tiempoVigilando;
        float tiempoPatrullando;
        float tiempoataque = 0;
        int tiempoEscaneando;
        core::vector3df posicion;

        core::vector3df posicionInicial;
        core::vector3df puntoInteres;
        core::vector3df cuboEnemigo;
        core::vector3df direccionHaciaProta;
        core::vector3df posicionAliado;
        core::vector3df direccionHaciaAliado;
        core::vector3df direccionHuir;
        core::vector3df posicionProta;
        f32 avMovement;
        Time tiempo;
        float time;
        float reloj;
        bool primeraVez;
        bool primeraVez2;
        bool primeraVez3;
        bool mensajePendiente;
        int mensajeEstado;
        Enemigo *compis[3];
        bool muerto;
        bool hayAliado;
        bool danyado;
        bool lul;
        bool lul2;
        bool lul3;
        bool creado = false;
        bool fabrica = false;
        bool devolver = false;
        PatrolRoute ruta;
        Player *player;

        b2RayCastInput input;
        b2RayCastOutput	output;

        b2RayCastInput input2;
        b2RayCastOutput	output2;

        PatrolPoint* pRuta;
        Fuzzy logica;
        scene::ISceneManager* smgr1;
        class World* iworld;
        Enemigo *aliado;



};

#endif // PLAYER_H
