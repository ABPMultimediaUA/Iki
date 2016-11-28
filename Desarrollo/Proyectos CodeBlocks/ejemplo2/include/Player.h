#ifndef PLAYER_H
#define PLAYER_H

#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

class Player
{
    public:
        Player();
        virtual ~Player();
        void inicializar(scene::ISceneManager*);
        void setCuboProta(core::vector3df);
        core::vector3df getCuboProta();
        scene::IMeshSceneNode* getModelo();

    protected:

    private:
        scene::IMeshSceneNode *modelo;
        core::vector3df cuboProta;

};

#endif // PLAYER_H
