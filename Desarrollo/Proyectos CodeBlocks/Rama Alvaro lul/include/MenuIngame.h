
#include <guilul.h>


using namespace irr;

using namespace core;   //Proposito general
using namespace scene;  //Escena 3D
using namespace video;  //Driver y rendering
using namespace io;     //Ficheros
using namespace gui;    //Interfaz de usuario

class MenuIngame
{
public:

	MenuIngame(video::IVideoDriver*, int, int, float);

	void run(video::IVideoDriver*, float, float, bool);

	float volumen;
	bool menupausa = false;

	void hud(video::IVideoDriver*, float, bool, int, int, float, float, int);


private:

    ITexture *image;
	bool options = false;
	bool opcionesresolucion = false;
	bool opcionescontrol = true;
	guilul *guiingame;


};


