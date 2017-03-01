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
    ITexture *image;
    if(t == 0)
        image = driver->getTexture("texturas/nuevapartidaboton.png");

    if(t == 1)
        image = driver->getTexture("texturas/salirboton.png");

    driver->draw2DImage(image, position2d<s32>(x, y), rect<s32>(0, 0, 240, 120), 0, SColor(255, 255, 255, 255), true);

}

void guilul::anyadirmenu(int x, int y, video::IVideoDriver* driver)
{
    ITexture *image;
    image = driver->getTexture("texturas/menu.png");

    driver->draw2DImage(image, position2d<s32>(x, y), rect<s32>(0, 0, 470, 690), 0, SColor(255, 255, 255, 255), true);
}
