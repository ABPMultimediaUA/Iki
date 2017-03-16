#include "GUI.h"
#include "GUI_Button.h"

GUI::GUI()
{
    //ctor
}

GUI::~GUI()
{
    //dtor
}

void GUI::anyadirboton(int t, int x, int y){
    boton.push_back(new GUI_Button(t, x, y));
}
