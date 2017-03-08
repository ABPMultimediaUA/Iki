#ifndef GAME_H
#define GAME_H

#include "Structs.h"
<<<<<<< HEAD
#include "Fachada/AnimatedMesh.h"
#include "Fachada/SceneNode.h"
#include "MyEventReceiver.h"
=======
#include "Vector2D.h"
#include "Fachada/SceneNode.h"
#include <Box2D/Box2D.h>
>>>>>>> refs/remotes/origin/master

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
        virtual bool               isPlayer()    { return false;    };

        virtual b2Body*            getBody(){return body;};
        virtual void               setBody(b2BodyDef bodyDef);
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
