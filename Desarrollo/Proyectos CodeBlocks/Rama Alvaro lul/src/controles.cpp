#include "controles.h"

controles::controles(int t, int x, int y, video::IVideoDriver* driver)
{
    if(t == 0){
        image = driver->getTexture("texturas/botonvolumen.png");
        image2 = driver->getTexture("texturas/verde.png");
    }
    else if(t == 1){
        image = driver->getTexture("texturas/resoluciondentro.png");
        image2 = driver->getTexture("texturas/checklleno.png");
    }
    tipo = t;
    posicionX = x;
    posicionY = y;
}

controles::~controles()
{
    //dtor
}

void controles::draw(video::IVideoDriver* driver){
if(tipo == 0){
    driver->draw2DImage(image2, position2d<s32>(posicionX+13, posicionY+9), rect<s32>(0, 0, barra, 70), 0, SColor(255, 255, 255, 255), true);
    driver->draw2DImage(image, position2d<s32>(posicionX, posicionY), rect<s32>(0, 0, 265, 90), 0, SColor(255, 255, 255, 255), true);
}
else if(tipo == 1){
    driver->draw2DImage(image, position2d<s32>(posicionX, posicionY), rect<s32>(0, 0, 214, 145), 0, SColor(255, 255, 255, 255), true);
        if(a)
    driver->draw2DImage(image2, position2d<s32>(posicionX+168, posicionY+15), rect<s32>(0, 0, 23, 23), 0, SColor(255, 255, 255, 255), true);
        else if(b)
    driver->draw2DImage(image2, position2d<s32>(posicionX+168, posicionY+42), rect<s32>(0, 0, 23, 23), 0, SColor(255, 255, 255, 255), true);
        else if(c)
    driver->draw2DImage(image2, position2d<s32>(posicionX+168, posicionY+71), rect<s32>(0, 0, 23, 23), 0, SColor(255, 255, 255, 255), true);
        else if(d)
    driver->draw2DImage(image2, position2d<s32>(posicionX+168, posicionY+100), rect<s32>(0, 0, 23, 23), 0, SColor(255, 255, 255, 255), true);
}

}
void controles::menos(){

    barra = barra - 22.2;


}

void controles::mas(){

    barra = barra + 22.2;


}



