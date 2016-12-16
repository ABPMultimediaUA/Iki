#ifndef MUROS_H
#define MUROS_H
#include <irrlicht.h>
#include <World.h>

using namespace irr;

class Muros
{
    public:
        Muros();
        virtual ~Muros();
        void inicializar(scene::ISceneManager*,video::IVideoDriver* driver);
        void setCuboMuros(core::vector3df);
        void setPosition(core::vector3df vec);
        core::vector3df getCuboMuros();
        scene::IMeshSceneNode* getModelo();
        b2Body* getBody();
    protected:

    private:
        scene::IMeshSceneNode *modelo;
        core::vector3df cuboMuros;
        b2Body *body2;
        int tam;
        class World* iworld;

};

#endif // MUROS_H
