#include "GUI_VolumeControl.h"

GUI_VolumeControl::GUI_VolumeControl()
{
    image  = new Image("texturas/botonvolumen.png");
    image2 = new Image("texturas/verde.png");

    posicionX = x;
    posicionY = y;

    posicionX2 = posicionX + 13;
    posicionY2 = posicionY + 9;

    rec       = {0, 0, 265, 90};
    rec2      = {0, 0, 22 * 10 , 23 };
}

GUI_VolumeControl::~GUI_VolumeControl()
{
    delete image;
    delete image2;
}

void GUI_VolumeControl::draw(){
    Structs::TColor color = {255, 255, 255, 255};
    image->draw(posicionX, posicionY, rec, color);
    image2->draw(posicionX2, posicionY2, rec2, color);
}
