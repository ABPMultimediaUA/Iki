#include "GUI/GUI_Button.h"
#include "Fachada/Image.h"
#include "SoundManager.h"

GUI_Button::GUI_Button(int x, int y, std::string cadena)
{
    cadena = "resources/texturas/"+cadena+".png";
    const char * c = cadena.c_str();
    image = new Image(c);

    posicionX = x;
    posicionY = y;
    rec       = {0  , 0  , 240, 120};
}

GUI_Button::~GUI_Button()
{
    delete image;
}
