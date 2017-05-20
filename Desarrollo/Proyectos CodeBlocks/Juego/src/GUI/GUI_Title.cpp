#include "GUI/GUI_Title.h"
#include "Fachada/Image.h"

GUI_Title::GUI_Title(int x, int y, std::string cadena)
{
    cadena = "resources/texturas/"+cadena+".png";
    const char * c = cadena.c_str();
    rec = {0, 0, 200, 50};
    image = new Image(c, rec);

    posicionX = x;
    posicionY = y;
}

GUI_Title::~GUI_Title()
{
    delete image;
}
