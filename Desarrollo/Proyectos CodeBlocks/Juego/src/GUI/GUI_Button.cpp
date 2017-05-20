#include "GUI/GUI_Button.h"
#include "Fachada/Image.h"
#include "SoundManager.h"

GUI_Button::GUI_Button(int x, int y, std::string cadena)
{
    cadena = "resources/texturas/"+cadena+".png";
    const char * c = cadena.c_str();
    rec       = {0  , 0  , 240, 120};
    image = new Image(c, rec);

    posicionX = x;
    posicionY = y;

}

GUI_Button::~GUI_Button()
{
    delete image;
}
