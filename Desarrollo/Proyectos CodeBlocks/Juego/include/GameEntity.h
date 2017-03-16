#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "Fachada/AnimatedMesh.h"
#include "Fachada/SceneNode.h"
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <iostream>
#include <map>
#include "Map.h"

class GameEntity
{
    public:
        GameEntity();
        ~GameEntity();

        //Getters
        virtual Structs::TPosicion getPosition() { return posicion; };
        virtual float              getVida()     { return vida;     };
        virtual float              getRadio()    { return radio;    };
        virtual bool               isPlayer()    { return false;    };

        virtual b2Body*            getBody(){return body;};
        virtual void               setBody(b2BodyDef bodyDef);
        virtual void               setMesh(AnimatedMesh* m){ aniMesh = m;};

        void registrarEntity(GameEntity* newE);
        //this method removes the entity from the list
        void borrarEntity(GameEntity* entity);

        GameEntity* getEntityByID(int id)const;

    protected:

        AnimatedMesh *aniMesh;
        SceneNode *modelo;
        b2Body *body;

        int id,nextID=0;
        float vida;
        Structs::TPosicion posicion;
        float radio;

    private:
        typedef std::map<int, GameEntity*> EntityMap;
};

#endif // GAME_H
