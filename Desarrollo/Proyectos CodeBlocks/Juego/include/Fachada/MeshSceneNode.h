#ifndef MESHSCENENODE_H
#define MESHSCENENODE_H

#include "Structs.h"

class MeshSceneNode
{
    public:
        MeshSceneNode(Structs::TMedida medida, Structs::TPosicion posicion, Structs::TColor color);
        MeshSceneNode(const std::string&);
        virtual ~MeshSceneNode();
        void setScale(Structs::TMedida);
        void setPosition(Structs::TPosicion);
        void setRotation(float);
        void setVisible(bool);

    protected:

    private:

        TNodo* node;
};

#endif // MESHSCENENODE_H
