#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "Structs.h"
#include "Enemies/Path/PathEdge.h"
#include "Fachada/AnimatedMesh.h"
#include "MyEventReceiver.h"
#include "Map.h"
#include "Enemies/StateMachine/Mensaje.h"
#include "EntityManager.h"
#include "SoundManager.h"

#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <iostream>
#include <map>


class GameEntity
{
    public:
        GameEntity();
        virtual ~GameEntity();

        //Getters
        virtual Structs::TPosicion getPosition() { return posicion; };
        virtual float              getVida()     { return vida;     };
        virtual float              getRadio()    { return radio;    };
        virtual bool               isPlayer()    { return false;    };
        virtual bool               isEnemy()     { return false;    };
        virtual bool               isTrigger()   { return false;    };
        virtual int                ID()          { return id;       };
        virtual bool               isPuertaAbierta(){return false;  };

        virtual b2Body*            getBody(){return body;};
        //virtual void               setBody(b2BodyDef bodyDef);
        virtual void               setMesh(AnimatedMesh* m){ aniMesh = m;};
        virtual bool               HandleMessage(const Mensaje& msg)=0;
        virtual bool               isPathObstructured(Structs::TPosicion)=0;
        virtual bool               canWalkBetween(Structs::TPosicion ,Structs::TPosicion)=0;
        virtual void               quitarVida(){if(vida>0) vida=vida-1;}
        virtual void               sumarVida(){vida=vida+1;}
        virtual void               setVida(float v){vida=v;}


    protected:

        AnimatedMesh *aniMesh;
        b2Body *body;

        int id,nextID;
        float vida;
        Structs::TPosicion posicion;
        float radio = 1.0;

};

#endif // GAME_H
