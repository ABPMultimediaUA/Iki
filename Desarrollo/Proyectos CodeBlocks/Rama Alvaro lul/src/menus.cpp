#include "menus.h"

menus::menus(int x, int y, video::IVideoDriver* driver)
{
        image = driver->getTexture("texturas/menu.png");

    posicionX = x;
    posicionY = y;
}

menus::~menus()
{
    //dtor
}

void menus::draw(video::IVideoDriver* driver){

    driver->draw2DImage(image, position2d<s32>(posicionX, posicionY), rect<s32>(0, 0, 460, 670), 0, SColor(255, 255, 255, 255), true);
}


