#ifndef ANIMATEDMESH_H
#define ANIMATEDMESH_H

#include "Structs.h"

class AnimatedMesh
{
    public:
        AnimatedMesh(const char* f, Structs::TColor color, Structs::TPosicion, float);
        virtual ~AnimatedMesh();

        void setScale(Structs::TMedida);
        void setScale(float);
        void setPosition(Structs::TPosicion);
        void setRotation(float);
        void setRotationXYZ(float,float,float);
        void setVisible(bool);
        Structs::TPosicion getPosition(){return posicion;}
        void cambiarColor(Structs::TColor color);
        void setTexture(const char* f);

    protected:

    private:
        IAnimatedMesh *mesh;
        IAnimatedMeshSceneNode *modelo;
        Structs::TPosicion posicion;
        float rotacion;
};

#endif // ANIMATEDMESH_H
