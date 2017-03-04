#ifndef TITULOS_H
#define TITULOS_H

#include <irrlicht.h>
#include <iostream>

using namespace irr;

using namespace core;   //Proposito general
using namespace scene;  //Escena 3D
using namespace video;  //Driver y rendering


class titulos
{
    public:
        titulos(int, int, int, video::IVideoDriver*);
        virtual ~titulos();
        void draw(video::IVideoDriver*);
        int posicionX;
        int posicionY;

    protected:
    private:
         ITexture *image;
         int tipo;


};

#endif
