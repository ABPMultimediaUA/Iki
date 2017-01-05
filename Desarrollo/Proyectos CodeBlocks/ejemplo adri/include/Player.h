#ifndef PLAYER_H
#define PLAYER_H

#include <irrlicht.h>
#include "driverChoice.h"
#include <World.h>



using namespace irr;

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
        core::vector3df getCuboProta();
        scene::IMeshSceneNode* getModelo();
        b2Body* getBody();
        float getVida();
        float velocidad;
        void setVida(float);
        void muerte();

    protected:

    private:
        scene::IMeshSceneNode *modelo;
        core::vector3df cuboProta;
        b2Body *body;
        int tam;
        float movx, movy;
        float vida;
        scene::ISceneManager* smgr1;
        class World* iworld;



};

#endif // PLAYER_H
