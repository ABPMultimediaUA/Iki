#ifndef MESHSCENENODE_H
#define MESHSCENENODE_H

#include "Structs.h"

class MeshSceneNode
{
    public:
        MeshSceneNode(Structs::TMedida medida, Structs::TPosicion posicion, Structs::TColor color);
        MeshSceneNode(const char*);
        virtual ~MeshSceneNode();
        void setScale(Structs::TMedida);
        void setPosition(Structs::TPosicion);
        void setRotation(float);
        void setVisible(bool);

    protected:

    private:

        IMesh* mesh;
        IMeshSceneNode* node;
};

#endif // MESHSCENENODE_H
