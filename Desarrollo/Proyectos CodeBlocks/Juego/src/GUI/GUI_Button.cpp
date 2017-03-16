#include "GUI_Button.h"
#include "Fachada/Image.h"

GUI_Button::GUI_Button(int t, int x, int y)
{
    switch(t){
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
    }

    posicionX = x;
    posicionY = y;
}

GUI_Button::~GUI_Button()
{
    delete image;
}

void GUI_Button::draw(){
    Structs::TColor      color = {235, 190, 190, 190};
    Structs::TRectangulo rec   = {0  , 0  , 240, 120};

    if(!estaencima)
        image->draw(posicionX, posicionY, rec, color);
    else{
        color = {255, 255, 255, 255};
        image->draw(posicionX, posicionY, rec, color);
    }
}

void GUI_Button::comprobarmouse(float x, float y){

    if((x > posicionX && x < posicionX + 240) && (y > posicionY && y < posicionY + 120))
        estaencima = true;
    else
        estaencima = false;
}
