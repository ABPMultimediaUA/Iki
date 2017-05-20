#include "GUI/GUI_Component.h"
#include "Fachada/Image.h"
#include "SoundManager.h"

GUI_Component::~GUI_Component()
{

}

void GUI_Component::draw(){
    Structs::TColor      color = {235, 190, 190, 190};

    if(!estaencima)
        image->draw(posicionX, posicionY);
    else{
        color = {255, 255, 255, 255};
        image->draw(posicionX, posicionY);
    }
}

int GUI_Component::comprobarmouse(float x, float y){

    if((x > posicionX && x < posicionX + rec.X_final) && (y > posicionY && y < posicionY + rec.Y_final)){
        estaencima = true;
        if(!sound_fired){
            //if (!SoundManager::getInstance()->isPlaying("menu_alante")){
                SoundMgr->playSonido("Menu/menu_alante");
                sound_fired = true;
            //}
        }
    }
    else{
        estaencima = false;
        sound_fired = false;
    }
    return 0;
}

void GUI_Component::setRect(int x, int y){
    rec.X_final = x;
    rec.Y_final = y;
}

void GUI_Component::reproducir_click(int type){
    if(type == 0)
        SoundMgr->playSonido("Menu/menu_alante2");
    else
        SoundMgr->playSonido("Menu/menu_atras");
}
