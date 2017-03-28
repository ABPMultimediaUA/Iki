#include "GUI/GUI_Title.h"
#include "Fachada/Image.h"

GUI_Title::GUI_Title(int x, int y, std::string cadena)
{
    cadena = "resources/texturas/"+cadena+".png";
    const char * c = cadena.c_str();
    image = new Image(c);

    posicionX = x;
    posicionY = y;
    rec = {0, 0, 200, 50};
}

GUI_Title::~GUI_Title()
{
    delete image;
}
