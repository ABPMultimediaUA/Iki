#ifndef MAPCOMPONENT_H
#define MAPCOMPONENT_H

#include "Structs.h"
#include "Fachada/AnimatedMesh.h"

class MapComponent
{
    public:
        MapComponent(Structs::TPosicion, int, int);
        ~MapComponent();

        int getName()   { return name;}
        int getConecta(){ return conecta;}
        Structs::TPosicion getPosition(){ return pos;}

    protected:

    private:
        //b2Body *body;
        int name, conecta;
        Structs::TPosicion pos;
        //AnimatedMesh *modelo;
};

#endif // MAPCOMPONENT_H
