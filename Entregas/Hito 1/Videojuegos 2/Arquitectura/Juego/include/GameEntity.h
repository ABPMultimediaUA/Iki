#ifndef GAME_H
#define GAME_H

#include <irrlicht.h>
#include <Box2D/Box2D.h>

using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;


class GameEntity
{
    public:
        GameEntity();
        virtual ~GameEntity();

    protected:
        IMeshSceneNode *modelo;
        int tipo;
        vector3df posicion;

};

#endif // GAME_H
