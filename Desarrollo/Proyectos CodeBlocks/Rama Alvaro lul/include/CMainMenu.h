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

	float volumen = 0.5;
	int resolucionX = 1360;
	int resolucionY = 768;


private:

    ITexture *image;
	IrrlichtDevice *MenuDevice;

	bool options = false;
	bool opcionesresolucion = false;

	bool start = false;

};

#endif

