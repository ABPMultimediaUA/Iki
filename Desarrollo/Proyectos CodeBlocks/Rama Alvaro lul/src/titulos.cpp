#include "titulos.h"

titulos::titulos(int t, int x, int y, video::IVideoDriver* driver)
{
    if(t == 0)
        image = driver->getTexture("texturas/titulovolumen.png");
    if(t == 1)
        image = driver->getTexture("texturas/resolucionboton.png");
    if(t == 2)
        image = driver->getTexture("texturas/controlestitulo.png");

    tipo = t;
    posicionX = x;
    posicionY = y;
}

titulos::~titulos()
{
    //dtor
}

void titulos::draw(video::IVideoDriver* driver)
{

    driver->draw2DImage(image, position2d<s32>(posicionX, posicionY), rect<s32>(0, 0, 200, 50), 0, SColor(255, 255, 255, 255), true);
}

void titulos::comprobarmouse3(float x, float y)
{

    if((y > posicionY && y < posicionY + 50) && (x > posicionX && x < posicionX + 200))
        estaencima = true;
    else
        estaencima = false;

}
