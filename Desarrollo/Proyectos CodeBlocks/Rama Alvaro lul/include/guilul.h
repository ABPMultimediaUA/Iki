#ifndef GUILUL_H
#define GUILUL_H

#include <irrlicht.h>
#include <stdio.h>
#include <botones.h>
#include <menus.h>
#include <controles.h>
#include <titulos.h>
#include "driverChoice.h"
#include <World.h>
#include "PatrolRoute.h"

using namespace irr;
using namespace core;   //Proposito general
using namespace scene;  //Escena 3D
using namespace video;  //Driver y rendering
using namespace std;


class guilul
{
    public:
        guilul();
        virtual ~guilul();
        void anyadirboton(int, int, int, video::IVideoDriver*);
        void anyadirtitulo(int, int, int, video::IVideoDriver*);
        void anyadircontrol(int, int, int, video::IVideoDriver*);
        void anyadirmenu(int, int, video::IVideoDriver*);
        void vidaprota(float, video::IVideoDriver*);
        void laserprota(bool, video::IVideoDriver*);
        vector<botones*> boton;
        vector<menus*> menu;
        vector<controles*> control;
        vector<titulos*> titulo;

    protected:
    private:

};

#endif // GUI_H
