#ifndef SCENENODE_H
#define SCENENODE_H

#include "Structs.h"
#include <iostream>

class SceneNode
{
    public:
        SceneNode(float tam, Structs::TPosicion posicionInicial);
        virtual ~SceneNode();
        Structs::TPosicion getPosition();
        void setPosition(Structs::TPosicion posicionNueva);
        void setRotation(float angulo);
        void cambiarColor(Structs::TColor color);
        IMeshSceneNode* getNode() {return node;};

    protected:

    private:
        IMeshSceneNode* node;
        Structs::TPosicion position;
};

#endif // SCENENODE_H
