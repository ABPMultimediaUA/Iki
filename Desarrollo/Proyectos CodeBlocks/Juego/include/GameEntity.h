#ifndef GAME_H
#define GAME_H

#include "Structs.h"
#include "SceneNode.h"
#include "MyEventReceiver.h"

#include <Box2D/Box2D.h>


class GameEntity
{
    public:
        GameEntity();
        ~GameEntity();
        Structs::TPosicion getPosition() { return posicion; }

    protected:
        SceneNode *modelo;
        b2Body *body;
        int tipo;
        Structs::TPosicion posicion;

};

#endif // GAME_H
