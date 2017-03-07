#ifndef GAME_H
#define GAME_H

#include "Structs.h"
#include "Fachada/AnimatedMesh.h"
#include "Fachada/SceneNode.h"
#include "MyEventReceiver.h"

#include <Box2D/Box2D.h>


class GameEntity
{
    public:
        GameEntity();
        ~GameEntity();

        //Getters
        virtual Structs::TPosicion getPosition() { return posicion; };
        virtual int                getTipo()     { return tipo;     };
        virtual float              getVida()     { return vida;     };
        virtual float              getRadio()    { return radio;    };
        virtual bool               isPlayer()    { return true;     };

        virtual void               setMesh(AnimatedMesh* m){ aniMesh = m;};


    protected:

        AnimatedMesh *aniMesh;
        SceneNode *modelo;
        b2Body *body;
        int tipo;
        float vida;
        Structs::TPosicion posicion;
        float radio;

};

#endif // GAME_H
