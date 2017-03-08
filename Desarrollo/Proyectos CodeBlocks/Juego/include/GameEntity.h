#ifndef GAME_H
#define GAME_H

#include "Structs.h"
#include "Vector2D.h"
#include "Fachada/SceneNode.h"
#include <Box2D/Box2D.h>


class GameEntity
{
    public:
        GameEntity();
        ~GameEntity();

        //Getters
        virtual float              getVida()     { return vida;     }
        virtual double             getRadio()    { return radio;    }
        virtual Structs::TPosicion getPosition() { return posicion; }
        virtual bool               isPlayer()    { return true;     }

    protected:

        SceneNode *modelo;
        b2Body *body;
        float vida;
        Structs::TPosicion posicion;
        double radio;

};

#endif // GAME_H
