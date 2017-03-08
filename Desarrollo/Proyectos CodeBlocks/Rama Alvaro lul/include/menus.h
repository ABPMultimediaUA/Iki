#ifndef MENUS_H
#define MENUS_H

#include <irrlicht.h>
#include <iostream>

using namespace irr;

using namespace core;   //Proposito general
using namespace scene;  //Escena 3D
using namespace video;  //Driver y rendering


class menus
{
    public:
        menus(int, int, video::IVideoDriver*);
        virtual ~menus();
        void draw(video::IVideoDriver*);
        ITexture *image;
         int posicionX;
         int posicionY;
         int tipo;

    protected:
    private:



};

#endif
