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
        controles(int, int, int, video::IVideoDriver*);
        virtual ~controles();
        void draw(video::IVideoDriver*);
        void mas();
        void menos();
        float barra = 111;
        int posicionX;
        int posicionY;
        bool a = true, b = false, c = false, d = false;

    protected:
    private:
         ITexture *image;
         ITexture *image2;
         int tipo;


};

#endif
