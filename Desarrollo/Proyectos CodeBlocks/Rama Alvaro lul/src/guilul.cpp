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

void guilul::anyadircontrol(int t, int x, int y, video::IVideoDriver* driver, float v)
{
    control.push_back(new controles(t, x, y, driver, v));

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
void guilul::laserprota(bool a, video::IVideoDriver* driver, int x, int y, float w, float z, int balas)
{
    int posicionx = (1240 * x)/1360;
    int posiciony = (650 * y)/768;

    ITexture *image = driver->getTexture("texturas/lasertocar.png");
    ITexture *image2 = driver->getTexture("texturas/leyendalaser.png");
    ITexture *image3 = driver->getTexture("texturas/numerobalas.png");

    if((w > posicionx && w < posicionx + 110) && (z > posiciony && z < posiciony + 109)){
    driver->draw2DImage(image2, position2d<s32>(posicionx-320, posiciony-150), rect<s32>(0, 0, 429, 164), 0, SColor(255, 255, 255, 255), true);
    driver->draw2DImage(image3, position2d<s32>(posicionx-205, posiciony-125), rect<s32>((balas*17), 0, (balas*17.5)+10, 16.9), 0, SColor(255, 255, 255, 255), true);
    }

    if(!a)
        driver->draw2DImage(image, position2d<s32>(posicionx, posiciony), rect<s32>(0, 0, 110, 109), 0, SColor(255, 255, 255, 255), true);
    else
        driver->draw2DImage(image, position2d<s32>(posicionx, posiciony), rect<s32>(0, 0, 110, 109), 0, SColor(255, 125, 125, 125), true);
}
