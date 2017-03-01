#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <irrlicht.h>
#include "driverChoice.h"
#include "../include/Time.h"
#include "../include/Fuzzy.h"
#include "../include/Muros.h"
#include <World.h>
#include <Player.h>
#include "../include/Map.h"
#include <iostream>

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
        void inicialiazar2(scene::ISceneManager*);
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
        bool getMuro();
        bool getCreado();
        bool seeWhereIgo();
        void moverBody(vector3df vec);

        void huir();
        int getTipo();
        int getID();
        bool isPathObstructured(vector3df destino);
        bool canWalkBetween(vector3df desde, vector3df hasta);
        std::list<vector3df> setLista(std::list<vector3df> lista){listaPosiciones=lista;}
        float velocidad;
        void setPosition(vector3df vec);
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
        float sospecha;
        float tiempoVigilando;
        int tiempoEscaneando;
        core::vector3df posicion;
        int i=0;
        float distanciaPlayer;
        float angulo;
        //std::list<vector3df>::iterator it;

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
        bool mensajePendiente;
        int mensajeEstado;
        Enemigo *compis[3];
        bool muerto;
        bool hayAliado;
        float rotacion;
        bool danyado;
        bool creado= false;
        bool devolver=false;
        Player *player;

        b2RayCastInput input;
        b2RayCastOutput	output;
        b2RayCastInput input2;
        b2RayCastOutput	output2;
        class Map* morito;

        PatrolPoint* pRuta;
        Fuzzy logica;
        scene::ISceneManager* smgr1;
        class World* iworld;
        Enemigo *aliado;

        ///PATHPLANNING
        //SparseGraph *grafo = Mapa->getNavGraph();
//        PathPlanner path2(enemigos[0],grafo);
        std::list<vector3df> listaPosiciones;
        std::list<vector3df>::iterator it2;
        vector3df posicionA;


};

#endif // PLAYER_H
