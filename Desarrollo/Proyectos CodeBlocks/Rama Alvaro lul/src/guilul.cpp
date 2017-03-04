#include "guilul.h"

guilul::guilul()
{
    //driver1 = driver;
}

guilul::~guilul()
{
    //dtor
}


void guilul::anyadirboton(int t, int x, int y, video::IVideoDriver* driver)
{
    boton.push_back(new botones(t, x, y, driver));

}

void guilul::anyadirtitulo(int t, int x, int y, video::IVideoDriver* driver)
{
    titulo.push_back(new titulos(t, x, y, driver));

}

void guilul::anyadircontrol(int t, int x, int y, video::IVideoDriver* driver)
{
    control.push_back(new controles(t, x, y, driver));

}


void guilul::anyadirmenu(int x, int y, video::IVideoDriver* driver)
{
    menu.push_back(new menus(x, y, driver));
}

void guilul::vidaprota(float a, video::IVideoDriver* driver)
{
    ITexture *image = driver->getTexture("texturas/vidaprota.png");

    if(a>=5)
        driver->draw2DImage(image, position2d<s32>(10, 10), rect<s32>(450, 0, 605, 250), 0, SColor(255, 255, 255, 255), true);
    else if(a>=4)
        driver->draw2DImage(image, position2d<s32>(10, 10), rect<s32>(340, 0, 445, 250), 0, SColor(255, 255, 255, 255), true);
    else if(a>=3)
        driver->draw2DImage(image, position2d<s32>(10, 10), rect<s32>(229, 0, 335, 250), 0, SColor(255, 255, 255, 255), true);
    else if(a>=2)
        driver->draw2DImage(image, position2d<s32>(10, 10), rect<s32>(119, 0, 225, 250), 0, SColor(255, 255, 255, 255), true);
    else if(a>=1)
        driver->draw2DImage(image, position2d<s32>(10, 10), rect<s32>(10, 0, 115, 250), 0, SColor(255, 255, 255, 255), true);
}
