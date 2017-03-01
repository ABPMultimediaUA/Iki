#ifndef GUILUL_H
#define GUILUL_H

#include <irrlicht.h>
#include <iostream>

using namespace irr;

using namespace core;   //Proposito general
using namespace scene;  //Escena 3D
using namespace video;  //Driver y rendering


class guilul
{
    public:
        guilul();
        virtual ~guilul();
        void anyadirboton(int, int, int, video::IVideoDriver*);
        void anyadirmenu(int, int, video::IVideoDriver*);

    protected:
    private:
        //video::IVideoDriver* driver1;

};

#endif // GUI_H
