#include "GUI/GUI_Button.h"
#include "Fachada/Image.h"

GUI_Button::GUI_Button(int x, int y, std::string cadena)
{

    cadena = "resources/texturas/"+cadena+".png";
    const char * c = cadena.c_str();
    image = new Image(c);
    /*switch(t){
    case 0:
        image = new Image("resources/texturas/nuevapartidaboton.png");
        break;
    case 1:
        image = new Image("resources/texturas/salirboton.png");
        break;
    case 2:
        image = new Image("resources/texturas/botonopciones.png");
        break;
    case 3:
        image = new Image("resources/texturas/botoncontinuar.png");
        break;
    case 4:
        image = new Image("resources/texturas/botonatras.png");
        break;
    case 5:
        image = new Image("resources/texturas/aceptarboton.png");
        break;
    default:
        break;
    }*/

    posicionX = x;
    posicionY = y;
    rec       = {0  , 0  , 240, 120};
}

GUI_Button::~GUI_Button()
{
    delete image;
}
