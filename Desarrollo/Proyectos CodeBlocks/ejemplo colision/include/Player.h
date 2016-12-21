#ifndef PLAYER_H
#define PLAYER_H

#include <irrlicht.h>
#include "driverChoice.h"
#include <World.h>
#include <Box2D/Box2D.h>



using namespace irr;

class Player
{
    public:
        Player();
        virtual ~Player();
        void inicializar(scene::ISceneManager*,video::IVideoDriver* driver);
        void setCuboProta(core::vector3df);
        void setPosicionBody(core::vector3df vec, float ang);
        void setPosicionModelo(b2Vec2 v);
        void moverBody(core::vector3df vec);
        core::vector3df getCuboProta();
        scene::IMeshSceneNode* getModelo();
        b2Body* getBody();

    protected:

    private:
        scene::IMeshSceneNode *modelo;
        core::vector3df cuboProta;
        b2Body *body;
        int tam;

        class World* iworld;



};

#endif // PLAYER_H