#ifndef PLAYER_ANIMADO_H
#define PLAYER_ANIMADO_H

#include <irrlicht.h>
#include "driverChoice.h"
#include <World.h>

#define MOV_SPEED 10.0f;


using namespace irr;

class Player_Animado
{
    public:
        Player_Animado();
        virtual ~Player_Animado();
        void inicializar(scene::ISceneManager*,video::IVideoDriver* driver);
        void setPosition(core::vector3df vec);
        void setRotarProta(core::vector3df vec);
        void setCuboProta(core::vector3df);
        void setPosicionBody(float ang);
        void moverBody(core::vector3df vec);
        core::vector3df getPosicionProta();
        scene::IAnimatedMesh* getModelo();
        b2Body* getBody();

    protected:

    private:
        scene::IMeshSceneNode *esfera;
        scene::IAnimatedMeshSceneNode *modelo;
        core::vector3df cuboProta, escalado1, escalado2;
        b2Body *body;
        scene::IAnimatedMesh* mesh;
        int tam;
        float movx, movy;

        class World* iworld;



};

#endif // Player_Animado_H
