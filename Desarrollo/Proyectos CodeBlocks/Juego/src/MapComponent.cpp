#include "MapComponent.h"
#include "Fachada/AnimatedMesh.h"
#include "PhisicsWorld.h"

MapComponent::MapComponent(Structs::TPosicion b, int n, int fin)
{
    pos = b;
    name = n;
    if(fin == 0)
        conecta = n + 1;
    else
        conecta = 0;
}

MapComponent::~MapComponent()
{
    pos      = {0,0,0};
    name     = -1;
    conecta  = -1;
}
