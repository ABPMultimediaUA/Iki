#ifndef ANIMACIONES_H
#define ANIMACIONES_H

#include "Structs.h"

class Animaciones
{
    public:
        Animaciones(std::string f, Structs::TColor color, Structs::TPosicion, float r,float frames,float inicio,const char* t, float scale );
        virtual ~Animaciones();

        void setScale(Structs::TMedida);
        void setScale(float);
        void setPosition(Structs::TPosicion);
        void setRotation(float);
        void setRotationXYZ(float,float,float);
        void setVisible(bool);
        Structs::TPosicion getPosition(){return {actual->getPosition().X,actual->getPosition().Y,actual->getPosition().Z};}
        void cambiarColor(Structs::TColor color);
        void setTexture(const char* f);
        std::vector <IAnimatedMeshSceneNode*> getModelosAnimacion(){return modelos;}
        IAnimatedMeshSceneNode* getActual(){return actual;}
        void setActual(IAnimatedMeshSceneNode *m){
                                                actual->setVisible(false);
                                                actual=m;
                                                actual->setVisible(true);}
        void Clear();

    protected:

    private:
        IAnimatedMesh *mesh;
        std::vector <IAnimatedMeshSceneNode*> modelos;
        IAnimatedMeshSceneNode *modelo;
        IAnimatedMeshSceneNode *actual;

        Structs::TPosicion posicion;
        float rotacion;
};

#endif // ANIMACIONES_H
