#ifndef MAPCOMPONENT_H
#define MAPCOMPONENT_H

#include "Structs.h"
#include "Fachada/AnimatedMesh.h"

class MapComponent
{
    public:
        MapComponent(float, Structs::TPosicion, int);
        ~MapComponent();
        b2Body *body;

    protected:

    private:
        AnimatedMesh *modelo;
};

#endif // MAPCOMPONENT_H
