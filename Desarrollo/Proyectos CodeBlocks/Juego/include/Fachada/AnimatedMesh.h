#ifndef ANIMATEDMESH_H
#define ANIMATEDMESH_H

#include "Structs.h"

class AnimatedMesh
{
    public:
        AnimatedMesh(const char* f, Structs::TColor color, Structs::TPosicion, float rotacion);
        virtual ~AnimatedMesh();

    protected:

    private:
        IAnimatedMesh *mesh;
        IAnimatedMeshSceneNode *modelo;
};

#endif // ANIMATEDMESH_H
