#include "GUI/GUI_Menu.h"
#include "Fachada/Image.h"

GUI_Menu::GUI_Menu(int x, int y, int t)
{
    if(t == 0){
        rec = {0, 0, 460, 670};
        image = new Image("resources/texturas/menu.png", rec);

        posicionX = x;
        posicionY = y;
        estaencima = false;

    }else{
        rec = {0, 0, 1360, 768};
        image = new Image("resources/texturas/ikifondo.png", rec);

        posicionX = x;
        posicionY = y;
        estaencima = false;


    }
}

GUI_Menu::~GUI_Menu()
{
    delete image;
}
