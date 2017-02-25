#ifndef PLAYER_H
#define PLAYER_H

#include <irrlicht.h>
#include "driverChoice.h"
#include <World.h>

#define MOV_SPEED 10.0f;



using namespace irr;

class Player
{
    public:
        Player();
        virtual ~Player();
        void inicializar(scene::ISceneManager*,video::IVideoDriver* driver);
        void setPosition(core::vector3df vec);
        void setCuboProta(core::vector3df);
        void moverBody(core::vector3df vec);
        core::vector3df getPosicionProta();
        core::vector3df getCuboProta();
        scene::IMeshSceneNode* getModelo();
        b2Body* getBody();
        int getLaser();
        float getVida();
        float velocidad;
        void setVida(float v);
        void setLaser(int l);
        void muerte();
        void setNoMuerto();
        bool sigilo = false;
        bool ismoving;

    protected:

    private:
        scene::IMeshSceneNode *modelo;
        core::vector3df cuboProta;
        b2Body *body;
        int tam, balas;
        float movx, movy;
        float vida;
        scene::ISceneManager* smgr1;
        class World* iworld;



};

#endif // PLAYER_H
