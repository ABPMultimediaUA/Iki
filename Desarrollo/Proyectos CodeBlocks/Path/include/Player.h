#ifndef PLAYER_H
#define PLAYER_H

#include <irrlicht.h>
#include "driverChoice.h"
#include <World.h>
#include "Map.h"

#define MOV_SPEED 10.0f;



using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;

class Player
{
    public:
        Player();
        virtual ~Player();
        void inicializar(scene::ISceneManager*,video::IVideoDriver* driver);
        void setPosition(core::vector3df vec);
        void setCuboProta(core::vector3df);
        void setPosicionBody(float ang);
        void moverBody(core::vector3df vec);
        bool cogerObjeto(core::vector3df, scene::ISceneManager*);
        bool atacar(core::vector3df, scene::ISceneManager*);
        core::vector3df getPosicionProta();
        core::vector3df getCuboProta();
        scene::IMeshSceneNode* getModelo();
        scene::IMeshSceneNode* getEsfera();
        b2Body* getBody();
        int getLaser();
        float getVida();
        void setVida(float v);
        void setLaser(int l);
        void muerte();
        void setNoMuerto();
        bool isPathObstructured(vector3df destino);
        void setMuro(Map* murito);
        float velocidad;

    protected:

    private:
        scene::IMeshSceneNode *modelo, *esfera;
        core::vector3df cuboProta, escalado;
        b2Body *body;
        int tam, balas;
        float movx, movy;
        float vida;
        scene::ISceneManager* smgr1;
        class World* iworld;
        b2RayCastInput input;
        b2RayCastOutput	output;
        class Map* mapa;
        float distancia;
        float angulo;
        scene::IMesh *rayo2;
        scene::IMeshSceneNode *modelo2;



};

#endif // PLAYER_H
