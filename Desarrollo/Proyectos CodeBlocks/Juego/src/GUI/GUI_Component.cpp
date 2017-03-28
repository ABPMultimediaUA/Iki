#include "GUI/GUI_Component.h"
#include "Fachada/Image.h"

GUI_Component::~GUI_Component()
{
    //dtor
}

void GUI_Component::draw(){
    Structs::TColor      color = {235, 190, 190, 190};

    if(!estaencima)
        image->draw(posicionX, posicionY, rec, color);
    else{
        color = {255, 255, 255, 255};
        image->draw(posicionX, posicionY, rec, color);
    }
}

int GUI_Component::comprobarmouse(float x, float y){

    if((x > posicionX && x < posicionX + rec.X_final) && (y > posicionY && y < posicionY + rec.Y_final))
        estaencima = true;
    else
        estaencima = false;
    return 0;
}

void GUI_Component::setRect(int x, int y){
    rec.X_final = x;
    rec.Y_final = y;
}
