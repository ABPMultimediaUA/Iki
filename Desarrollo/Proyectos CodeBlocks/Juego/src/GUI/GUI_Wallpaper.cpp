#include "GUI_Wallpaper.h"
#include "Fachada/Image.h"

GUI_Wallpaper::GUI_Wallpaper(std::string cadena)
{
    cadena = "resources/texturas/"+cadena+".png";
    const char * c = cadena.c_str();
    image = new Image(c);

    posicionX = 0;
    posicionY = 0;
    estaencima = false;

    rec = {0, 0, 1360, 768};
}

GUI_Wallpaper::~GUI_Wallpaper()
{
    delete image;
}
