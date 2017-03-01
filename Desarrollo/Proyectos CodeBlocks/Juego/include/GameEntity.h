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
        virtual Structs::TPosicion getPosition() { return posicion; }
        virtual int                getTipo()     { return tipo;     }
        virtual float              getVida()     { return vida;     }
        virtual double             getRadio()    { return radio;    }
        virtual bool               isPlayer()    { return true;     };



    protected:

        SceneNode *modelo;
        b2Body *body;
        int tipo;
        float vida;
        Structs::TPosicion posicion;
        double radio;

};

#endif // GAME_H
