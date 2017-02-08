#ifndef PHISICSWORLD_H
#define PHISICSWORLD_H

#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include "MeshSceneNode.h"

using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;


class PhisicsWorld
{
    public:
        static PhisicsWorld& getInstance() {
            static PhisicsWorld singleton;
            return singleton;
        };
        virtual ~PhisicsWorld();
        void Step(float DeltaTime);
        b2World* getWorld(){return phisics_world;};

    protected:

    private:
        PhisicsWorld();
        b2World* phisics_world;
        b2Vec2 gravity;
};

#endif // PHISICSWORLD_H
