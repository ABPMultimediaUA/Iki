#ifndef CONTROLES_H
#define CONTROLES_H

#include <irrlicht.h>
#include <iostream>

using namespace irr;

using namespace core;   //Proposito general
using namespace scene;  //Escena 3D
using namespace video;  //Driver y rendering


class controles
{
    public:
        controles(int, int, int, video::IVideoDriver*, float);
        virtual ~controles();
        void draw(video::IVideoDriver*);
        void mas();
        void menos();
        float barra;
        int posicionX;
        int posicionY;
        bool a = true, b = false, c = false, d = false;
        bool estaencima1 = false, estaencima2 = false, estaencima3 = false, estaencima4 = false;
        void comprobarmouse(float, float);
        bool estaencimamas = true;
        bool estaencimamenos = false;
        void comprobarmouse2(float, float);


    protected:
    private:
         ITexture *image;
         ITexture *image2;
         int tipo;


};

#endif
