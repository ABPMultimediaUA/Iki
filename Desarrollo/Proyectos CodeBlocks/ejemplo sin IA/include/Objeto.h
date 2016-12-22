#ifndef OBJETO_H
#define OBJETO_H

#include <irrlicht.h>
#include "driverChoice.h"
#include <World.h>

using namespace irr;
class Objeto
{
    public:
        Objeto();
        void inicializar(scene::ISceneManager*,video::IVideoDriver* driver);
        void setPosition(core::vector3df vec);
        void setCuboProta(core::vector3df);
        void setPosicionBody(float ang);
        virtual ~Objeto();
        core::vector3df getCuboProta();
        scene::IMeshSceneNode* getModelo();
        b2Body* getBody();

    protected:

    private:
        scene::IMeshSceneNode *modelo;
        core::vector3df cuboProta;
        b2Body *body;
        int tam;
        float movx, movy;

        class World* iworld;
};

#endif // OBJETO_H