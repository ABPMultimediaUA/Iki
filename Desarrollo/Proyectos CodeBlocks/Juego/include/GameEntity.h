#ifndef GAME_H
#define GAME_H

#include "Structs.h"
#include "Fachada/SceneNode.h"
#include "MyEventReceiver.h"

#include <Box2D/Box2D.h>


class GameEntity
{
    public:
        GameEntity();
        ~GameEntity();

        //Getters
        Structs::TPosicion getPosition() { return posicion; }
        int                getTipo()     { return tipo;     }
        float              getVida()     { return vida;     }
        double             getRadio()    { return radio;    }

    protected:

        SceneNode *modelo;
        b2Body *body;
        int tipo;
        float vida;
        Structs::TPosicion posicion;
        double radio;

};

#endif // GAME_H
