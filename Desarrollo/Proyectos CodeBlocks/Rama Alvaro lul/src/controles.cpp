#include "controles.h"

controles::controles(int t, int x, int y, video::IVideoDriver* driver, float volumen)
{
    if(t == 0)
    {
        image = driver->getTexture("texturas/botonvolumen.png");
        image2 = driver->getTexture("texturas/verde.png");
    }
    else if(t == 1)
    {
        image = driver->getTexture("texturas/resoluciondentro.png");
        image2 = driver->getTexture("texturas/checklleno.png");
    }
    else if(t == 2)
    {
        image = driver->getTexture("texturas/controlespanel.png");
    }
    tipo = t;
    posicionX = x;
    posicionY = y;
    barra = volumen * 22 * 10;
}

controles::~controles()
{
    //dtor
}

void controles::draw(video::IVideoDriver* driver)
{
    if(tipo == 0)
    {
        driver->draw2DImage(image2, position2d<s32>(posicionX+13, posicionY+9), rect<s32>(0, 0, barra, 70), 0, SColor(255, 255, 255, 255), true);
        driver->draw2DImage(image, position2d<s32>(posicionX, posicionY), rect<s32>(0, 0, 265, 90), 0, SColor(255, 255, 255, 255), true);
    }
    else
    {
        driver->draw2DImage(image, position2d<s32>(posicionX, posicionY), rect<s32>(0, 0, 214, 145), 0, SColor(255, 255, 255, 255), true);
        if(tipo == 1){
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

}
void controles::menos()
{

    barra = barra - 22.2;


}

void controles::mas()
{

    barra = barra + 22.2;


}

void controles::comprobarmouse2(float x, float y)
{
    if(tipo == 0)
    {

        if((y > posicionY && y < posicionY + 90))
        {
            if((x > posicionX && x < posicionX + 130))
            {
                estaencimamenos = true;
                estaencimamas = false;
            }

            else if((x > posicionX + 130 && x < posicionX + 260))
            {
                estaencimamas = true;
                estaencimamenos = false;

            }
        }
        else
        {
            estaencimamas = false;
            estaencimamenos = false;
        }
    }
    else if (tipo == 1)
    {
        if((x > posicionX+10 && x < posicionX +200))
        {
            if((y > posicionY+10 && y < posicionY + 41.25)){
            estaencima1 = true;
            estaencima2 = false;
            estaencima3 = false;
            estaencima4 = false;
            }
            else if((y > posicionY+41.25 && y < posicionY + 72.50)){
            estaencima2 = true;
            estaencima1 = false;
            estaencima3 = false;
            estaencima4 = false;
            }
            else if((y > posicionY+72.50 && y < posicionY + 103.75)){
            estaencima3 = true;
            estaencima2 = false;
            estaencima1 = false;
            estaencima4 = false;
            }
            else if((y > posicionY+103.75 && y < posicionY + 135)){
            estaencima4 = true;
            estaencima2 = false;
            estaencima3 = false;
            estaencima1 = false;
            }
            else{
            estaencima4 = false;
            estaencima2 = false;
            estaencima3 = false;
            estaencima1 = false;

        }

        }
        else{
            estaencima4 = false;
            estaencima2 = false;
            estaencima3 = false;
            estaencima1 = false;

        }


    }
}


