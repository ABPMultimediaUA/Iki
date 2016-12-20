#ifndef MUROS_H
#define MUROS_H
#include <irrlicht.h>
#include <World.h>
#include <iostream>

using namespace irr;
using namespace scene;


class Muros
{
    public:
        Muros();
        virtual ~Muros();
        void inicializar(scene::ISceneManager*,video::IVideoDriver* driver, core::vector3df pos);
        void setCuboMuros(core::vector3df);
        void setPosition(core::vector3df vec);
        core::vector3df getCuboMuros();
        scene::IMeshSceneNode* getModelo();
        b2Body* getBody();
    protected:

    private:
        core::vector3df cuboMuros;
        int dim;
        float tam, tam10, tam15, tam25, tam30, tam40;
        class World* iworld;
        IMesh *tipo1;
        IMeshSceneNode* modelo;
        b2Body *body;

};

#endif // MUROS_H

