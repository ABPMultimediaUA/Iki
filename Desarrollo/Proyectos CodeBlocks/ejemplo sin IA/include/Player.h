
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
        void setPosicionBody(float ang);
        void moverBody(core::vector3df vec);
        void setRotarProta(core::vector3df vec);
        bool cogerObjeto(core::vector3df, scene::ISceneManager*);
        core::vector3df getPosicionProta();
        scene::IMeshSceneNode* getModelo();
        b2Body* getBody();

    protected:

    private:
        scene::IMeshSceneNode *modelo, *esfera;
        core::vector3df cuboProta, escalado;
        b2Body *body;
        int tam;
        float movx, movy;

        class World* iworld;



};

#endif // PLAYER_H
