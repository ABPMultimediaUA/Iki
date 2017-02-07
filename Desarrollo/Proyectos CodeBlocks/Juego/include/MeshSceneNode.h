#ifndef MESHSCENENODE_H
#define MESHSCENENODE_H

#include "Structs.h"
#include <iostream>

class MeshSceneNode
{
    public:
        MeshSceneNode(Structs::TMedida medida, Structs::TPosicion posicion, Structs::TColor color);
        ~MeshSceneNode();

    protected:

    private:
        IMesh *mesh;
        IMeshSceneNode *node;
};

#endif // MESHSCENENODE_H
