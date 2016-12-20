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
        void inicializar(scene::ISceneManager*,video::IVideoDriver* driver);
        void setCuboProta(core::vector3df);
        void setRotationProta(float);
        core::vector3df getCuboProta();
        scene::IMeshSceneNode* getModelo();
        float getVida();
        void matar();
        bool estaMuerto();

    protected:

    private:
        scene::IMeshSceneNode *modelo;
        core::vector3df cuboProta;
        float vida;
        bool muerto;

};

#endif // PLAYER_H
