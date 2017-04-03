#include "GUI/GUI_VolumeControl.h"
#include "Fachada/Image.h"
#include "SoundManager.h"

GUI_VolumeControl::GUI_VolumeControl(int x, int y)
{
    image  = new Image("resources/texturas/botonvolumen.png");
    image2 = new Image("resources/texturas/verde.png");

    posicionX = x;
    posicionY = y;

    posicionX2 = posicionX + 13;
    posicionY2 = posicionY + 9;

    volumen   = SoundManager::getInstance()->getVolumen();

    rec       = {0, 0, 265, 90};
    rec2      = {0, 0, 22 * (volumen * 10.f) , 70 };

}

GUI_VolumeControl::~GUI_VolumeControl()
{
    delete image;
    delete image2;
}

void GUI_VolumeControl::subirVolumen(){
    if(rec2.X_final < 220){
        rec2.X_final = rec2.X_final + 22;
        volumen += 0.1f;
        SoundManager::getInstance()->volumenGeneral(volumen);
    }
}

void GUI_VolumeControl::bajarVolumen(){
    if(rec2.X_final > 0){
        rec2.X_final = rec2.X_final - 22;
        volumen -= 0.1f;
        SoundManager::getInstance()->volumenGeneral(volumen);
    }
}

void GUI_VolumeControl::draw(){
    Structs::TColor color = {255, 255, 255, 255};
    image2->draw(posicionX2, posicionY2, rec2, color);
    image->draw(posicionX, posicionY, rec, color);
}

int GUI_VolumeControl::comprobarmouse(float x, float y){

    if(y > posicionY && y < posicionY + 90){
        if(x > posicionX && x < posicionX + 130){
            estaencima = true;
            bajarVolumen();
        }
        else if(x > posicionX + 130 && x < posicionX + 260){
            estaencima = true;
            subirVolumen();
        }
    }
    return 0;
}
