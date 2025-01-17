#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <irrlicht.h>
#include "driverChoice.h"
#include <World.h>


using namespace irr;

class Enemigo
{
    public:
        Enemigo();
        virtual ~Enemigo();
        void inicializar(scene::ISceneManager*,video::IVideoDriver* driver);
        void inicializar2(scene::ISceneManager*,video::IVideoDriver* driver);
        void setCuboEnemigo(core::vector3df);
        void setPosition(core::vector3df vec);
        core::vector3df getCuboEnemigo();
        scene::IMeshSceneNode* getModelo();
        b2Body* getBody();
        void escuchandoR();
        void noescuchandoR();
        bool getEscuchando();
        bool comprobarPunto(b2Vec2);
        void quitarVida();
        void setDanyado(bool);
        bool getDanyado();
        bool getMuerto();

    protected:

    private:
        scene::IMesh *mura1;
        scene::IMeshSceneNode *modelo;
        core::vector3df cuboEnemigo;
        b2Body *body2;
        int tam;
        int vida;
        //bool escuchando;
        bool danyado;
        bool muerto;

        class World* iworld;



};

#endif // PLAYER_H
