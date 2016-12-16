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
        core::vector3df getCuboProta();
        scene::IMeshSceneNode* getModelo();

    protected:

    private:
        scene::IMeshSceneNode *modelo;
        core::vector3df cuboProta;
        b2Body *body;
        int tam;

        class World* iworld;



};

#endif // PLAYER_H
