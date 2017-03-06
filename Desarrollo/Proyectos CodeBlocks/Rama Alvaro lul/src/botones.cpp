#include "botones.h"

botones::botones(int t, int x, int y, video::IVideoDriver* driver)
{
    if(t == 0)
        image = driver->getTexture("texturas/nuevapartidaboton.png");

    else if(t == 1)
        image = driver->getTexture("texturas/salirboton.png");

    else if(t == 2)
        image = driver->getTexture("texturas/botonopciones.png");

    else if(t == 3)
        image = driver->getTexture("texturas/botoncontinuar.png");

    else if(t == 4)
        image = driver->getTexture("texturas/botonatras.png");

    else if(t == 5)
        image = driver->getTexture("texturas/aceptarboton.png");

    tipo = t;
    posicionX = x;
    posicionY = y;
}

botones::~botones()
{
    //dtor
}

void botones::draw(video::IVideoDriver* driver){
    if(!estaencima)
    driver->draw2DImage(image, position2d<s32>(posicionX, posicionY), rect<s32>(0, 0, 240, 120), 0, SColor(235, 190, 190, 190), true);
    else
        driver->draw2DImage(image, position2d<s32>(posicionX, posicionY), rect<s32>(0, 0, 240, 120), 0, SColor(255, 255, 255, 255), true);
}

void botones::comprobarmouse(float x, float y){

    if((x > posicionX && x < posicionX + 240) && (y > posicionY && y < posicionY + 120))
        estaencima = true;

        else
            estaencima = false;


}
