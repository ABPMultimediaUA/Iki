#ifndef BOTONES_H
#define BOTONES_H

#include <irrlicht.h>
#include <iostream>

using namespace irr;

using namespace core;   //Proposito general
using namespace scene;  //Escena 3D
using namespace video;  //Driver y rendering


class botones
{
    public:
        botones(int, int, int, video::IVideoDriver*);
        virtual ~botones();
        void draw(video::IVideoDriver*);
        void comprobarmouse(float, float);
        int posicionX;
        int posicionY;
        bool estaencima = false;

    protected:
    private:
         ITexture *image;
         int tipo;


};

#endif
