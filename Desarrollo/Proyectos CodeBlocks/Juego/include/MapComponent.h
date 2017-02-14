#ifndef MAPCOMPONENT_H
#define MAPCOMPONENT_H

#include "Structs.h"
#include "AnimatedMesh.h"
#include "PhisicsWorld.h"

class MapComponent
{
    public:
        MapComponent(float, Structs::TPosicion, int);
        ~MapComponent();

    protected:

    private:

        b2Body *body;
        AnimatedMesh *modelo;
};

#endif // MAPCOMPONENT_H
