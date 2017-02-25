#ifndef __C_MAIN_MENU_H_INCLUDED__
#define __C_MAIN_MENU_H_INCLUDED__

#include <guilul.h>

using namespace irr;

using namespace core;   //Proposito general
using namespace scene;  //Escena 3D
using namespace video;  //Driver y rendering
using namespace io;     //Ficheros
using namespace gui;    //Interfaz de usuario

class CMainMenu
{
public:

	CMainMenu();

	bool run();


private:

    ITexture *image;
	IrrlichtDevice *MenuDevice;

	bool start = false;

};

#endif

