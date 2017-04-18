#include "GUI/GUI_Menu.h"
#include "Fachada/Image.h"

GUI_Menu::GUI_Menu(int x, int y, int t)
{
    if(t == 0){
        image = new Image("resources/texturas/menu.png");

        posicionX = x;
        posicionY = y;
        estaencima = false;

        rec = {0, 0, 460, 670};
    }else{
        image = new Image("resources/texturas/ikifondo.png");

        posicionX = x;
        posicionY = y;
        estaencima = false;

        rec = {0, 0, 1360, 768};
    }
}

GUI_Menu::~GUI_Menu()
{
    delete image;
}
