// This is a Demo of the Irrlicht Engine (c) 2005-2009 by N.Gebhardt.
// This file is not documented.

#include "CMainMenu.h"
#include "MyEventReceiver.h"



CMainMenu::CMainMenu()
{

}


bool CMainMenu::run()
{

    MyEventReceiver receiver;

    MenuDevice = createDevice(video::EDT_OPENGL,core::dimension2d<u32>(resolucionX, resolucionY), 16, false, false, false, &receiver);

    video::IVideoDriver* driver = MenuDevice->getVideoDriver();
    scene::ISceneManager* smgr = MenuDevice->getSceneManager();
    guilul *guipropio = new guilul;


    core::stringw str = "Irrlicht Engine Demo v";
    str += MenuDevice->getVersion();
    MenuDevice->setWindowCaption(str.c_str());

    guipropio->anyadirmenu(400, 60, driver);
    guipropio->anyadirboton(0, 540, 160, driver);
    guipropio->anyadirboton(2, 540, 300, driver);
    guipropio->anyadirboton(1, 540, 440, driver);
    guipropio->anyadirtitulo(0, 570, 125, driver);
    guipropio->anyadircontrol(0, 540, 175, driver, volumen);
    guipropio->anyadirtitulo(1, 570, 270, driver);
    guipropio->anyadirtitulo(2, 570, 340, driver);
    guipropio->anyadirboton(4, 540, 540, driver);
    guipropio->anyadircontrol(1, 565, 320, driver, volumen);
    guipropio->anyadircontrol(2, 565, 390, driver, volumen);



    while(MenuDevice->run())
    {
        if (MenuDevice->isWindowActive())
        {
            driver->beginScene(false, true, video::SColor(0,0,0,0));

            if(!options)
            {
                guipropio->menu.at(0)->draw(driver);
                for(int i = 0; i<=2; i++)
                {
                    guipropio->boton.at(i)->draw(driver);
                    guipropio->boton.at(i)->comprobarmouse(receiver.GetMouseState().Position.X, receiver.GetMouseState().Position.Y);
                }

                if(receiver.GetMouseState().LeftButtonDown)
                {
                    if(guipropio->boton.at(0)->estaencima)
                    {
                        MenuDevice->closeDevice();
                        start = true;

                    }
                    else if(guipropio->boton.at(1)->estaencima)
                    {
                        options = true;

                    }
                    else if(guipropio->boton.at(2)->estaencima)
                    {
                        MenuDevice->closeDevice();
                        exit(0);
                    }
                }
            }
            else
            {
                if(!opcionesresolucion && !opcionescontrol)
                {
                    guipropio->menu.at(0)->draw(driver);
                    guipropio->titulo.at(0)->draw(driver);
                    guipropio->control.at(0)->draw(driver);
                    guipropio->boton.at(3)->draw(driver);
                    guipropio->titulo.at(1)->draw(driver);
                    guipropio->titulo.at(2)->draw(driver);

                    guipropio->boton.at(3)->comprobarmouse(receiver.GetMouseState().Position.X, receiver.GetMouseState().Position.Y);
                    guipropio->control.at(0)->comprobarmouse2(receiver.GetMouseState().Position.X, receiver.GetMouseState().Position.Y);
                    guipropio->titulo.at(1)->comprobarmouse3(receiver.GetMouseState().Position.X, receiver.GetMouseState().Position.Y);
                    guipropio->titulo.at(2)->comprobarmouse3(receiver.GetMouseState().Position.X, receiver.GetMouseState().Position.Y);


                    if(receiver.GetMouseState().LeftButtonDown)
                    {
                        if(guipropio->boton.at(3)->estaencima){

                                options = false;
                        }
                        else if(guipropio->control.at(0)->estaencimamenos)
                        {

                                if(volumen > 0)
                                {
                                    guipropio->control.at(0)->menos();
                                    volumen = volumen - 0.1;
                                }
                            }
                            else if(guipropio->control.at(0)->estaencimamas)
                            {
                                if(volumen < 1)
                                {
                                    guipropio->control.at(0)->mas();
                                    volumen = volumen + 0.1;
                                }
                            }

                        if(guipropio->titulo.at(1)->estaencima)
                                opcionesresolucion = true;

                        if(guipropio->titulo.at(2)->estaencima)
                                opcionescontrol = true;



                    }
                }
                else if(opcionesresolucion)
                {
                    guipropio->control.at(1)->draw(driver);
                    guipropio->control.at(1)->comprobarmouse2(receiver.GetMouseState().Position.X, receiver.GetMouseState().Position.Y);

                    if(receiver.GetMouseState().LeftButtonDown)
                    {
                        if(guipropio->control.at(1)->estaencima1){
                                guipropio->control.at(1)->a = true;
                                guipropio->control.at(1)->b = false;
                                guipropio->control.at(1)->c = false;
                                guipropio->control.at(1)->d = false;
                                resolucionX = 1360;
                                resolucionY = 768;


                            }
                            else if(guipropio->control.at(1)->estaencima2)
                            {
                                guipropio->control.at(1)->a = false;
                                guipropio->control.at(1)->b = true;
                                guipropio->control.at(1)->c = false;
                                guipropio->control.at(1)->d = false;
                                resolucionX = 1280;
                                resolucionY = 720;

                            }
                            else if(guipropio->control.at(1)->estaencima3)
                            {
                                guipropio->control.at(1)->a = false;
                                guipropio->control.at(1)->b = false;
                                guipropio->control.at(1)->c = true;
                                guipropio->control.at(1)->d = false;
                                resolucionX = 1024;
                                resolucionY = 768;

                            }
                            else if(guipropio->control.at(1)->estaencima4)
                            {
                                guipropio->control.at(1)->a = false;
                                guipropio->control.at(1)->b = false;
                                guipropio->control.at(1)->c = false;
                                guipropio->control.at(1)->d = true;
                                resolucionX = 768;
                                resolucionY = 576;

                            }
                            else
                                opcionesresolucion = false;


                    }
                }
                else if(opcionescontrol){
                    guipropio->control.at(2)->draw(driver);
                    if(receiver.GetMouseState().LeftButtonDown)
                    opcionescontrol = false;

                }

            }


            driver->endScene();
        }
    }

    MenuDevice->drop();





    return start;
}
