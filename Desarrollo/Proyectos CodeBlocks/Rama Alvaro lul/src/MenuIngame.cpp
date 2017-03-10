// This is a Demo of the Irrlicht Engine (c) 2005-2009 by N.Gebhardt.
// This file is not documented.

#include "MenuIngame.h"

MenuIngame::MenuIngame(video::IVideoDriver* driver, int x, int y, float v)
{

    volumen = v;
    guiingame = new guilul;
    guiingame->anyadirmenu((400 * x)/1360, (60 * y)/768, driver);
    guiingame->anyadirboton(3, (540 * x)/1360, (160 * y)/768, driver);
    guiingame->anyadirboton(1, (540 * x)/1360, (440 * y)/768, driver);
    guiingame->anyadirboton(2, (540 * x)/1360, (300 * y)/768, driver);
    guiingame->anyadirtitulo(0, 570, 125, driver);
    guiingame->anyadircontrol(0, 540, 175, driver, volumen);
    guiingame->anyadirboton(4, 540, 540, driver);
    guiingame->anyadircontrol(2, 565, 390, driver, volumen);
    guiingame->anyadirtitulo(2, 570, 340, driver);


}


void MenuIngame::run(video::IVideoDriver* driver, float x, float y, bool click)
{
if(!options)
            {
    guiingame->menu.at(0)->draw(driver);
    guiingame->boton.at(0)->draw(driver);
    guiingame->boton.at(1)->draw(driver);
    guiingame->boton.at(2)->draw(driver);
    for(int i = 0; i<=2; i++)
                {
                    guiingame->boton.at(i)->draw(driver);
                    guiingame->boton.at(i)->comprobarmouse(x, y);
                }

            if(click){
                if(guiingame->boton.at(0)->estaencima)
                    {
                        menupausa = false;

                    }
                    else if(guiingame->boton.at(2)->estaencima)
                    {
                        options = true;
                    }
                    else if(guiingame->boton.at(1)->estaencima)
                    {
                        //device->closeDevice();
                        exit(0);
                    }
                }

    }
    else{
            if(!opcionescontrol){
                    guiingame->menu.at(0)->draw(driver);
                    guiingame->titulo.at(0)->draw(driver);
                    guiingame->control.at(0)->draw(driver);
                    guiingame->boton.at(3)->draw(driver);
                    guiingame->titulo.at(1)->draw(driver);

                    guiingame->boton.at(3)->comprobarmouse(x, y);
                    guiingame->control.at(0)->comprobarmouse2(x, y);
                    guiingame->titulo.at(1)->comprobarmouse3(x, y);

                    if(click){
                        if(guiingame->boton.at(3)->estaencima){

                                options = false;
                        }
                        else if(guiingame->control.at(0)->estaencimamenos)
                        {

                                if(volumen > 0)
                                {
                                    guiingame->control.at(0)->menos();
                                    volumen = volumen - 0.1;
                                }
                            }
                            else if(guiingame->control.at(0)->estaencimamas)
                            {
                                if(volumen < 1)
                                {
                                    guiingame->control.at(0)->mas();
                                    volumen = volumen + 0.1;
                                }
                            }
                            else if(guiingame->titulo.at(1)->estaencima)
                                opcionescontrol = true;
                    }
            }else{
                    guiingame->menu.at(0)->draw(driver);
                    guiingame->titulo.at(0)->draw(driver);
                    guiingame->control.at(0)->draw(driver);
                    guiingame->boton.at(3)->draw(driver);
                    guiingame->titulo.at(1)->draw(driver);
                    guiingame->control.at(1)->draw(driver);
                    if(click)
                    opcionescontrol = false;
            }
    }

}

    void MenuIngame::hud(video::IVideoDriver* driver, float vida, bool laser, int resolucionx, int resoluciony, float x, float y, int b){

            guiingame->vidaprota(vida, driver);
            guiingame->laserprota(laser, driver, resolucionx, resoluciony, x, y, b);
    }




