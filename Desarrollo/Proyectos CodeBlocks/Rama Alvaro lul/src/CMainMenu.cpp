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
    guipropio->anyadircontrol(0, 540, 175, driver);
    guipropio->anyadirtitulo(1, 570, 270, driver);
    guipropio->anyadirboton(4, 540, 540, driver);
    guipropio->anyadircontrol(1, 565, 320, driver);


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
                }

                if(receiver.GetMouseState().LeftButtonDown)
                {
                    if(receiver.GetMouseState().Position.X > guipropio->boton.at(0)->posicionX && receiver.GetMouseState().Position.X < guipropio->boton.at(0)->posicionX + 240)
                    {
                        if(receiver.GetMouseState().Position.Y > guipropio->boton.at(0)->posicionY && receiver.GetMouseState().Position.Y < guipropio->boton.at(0)->posicionY + 120)
                        {
                            MenuDevice->closeDevice();
                            start = true;

                        }
                        else if(receiver.GetMouseState().Position.Y > guipropio->boton.at(1)->posicionY && receiver.GetMouseState().Position.Y < guipropio->boton.at(1)->posicionY + 120)
                        {
                            options = true;

                        }
                        else if(receiver.GetMouseState().Position.Y > guipropio->boton.at(2)->posicionY && receiver.GetMouseState().Position.Y < guipropio->boton.at(2)->posicionY + 120)
                        {
                            MenuDevice->closeDevice();
                            exit(0);
                        }
                    }
                }
            }
            else
            {
                if(!opcionesresolucion)
                {
                    guipropio->menu.at(0)->draw(driver);
                    guipropio->titulo.at(0)->draw(driver);
                    guipropio->control.at(0)->draw(driver);
                    guipropio->boton.at(3)->draw(driver);
                    guipropio->titulo.at(1)->draw(driver);


                    if(receiver.GetMouseState().LeftButtonDown)
                    {
                        if(receiver.GetMouseState().Position.Y > guipropio->boton.at(3)->posicionY && receiver.GetMouseState().Position.Y < guipropio->boton.at(3)->posicionY + 120)
                        {
                            if(receiver.GetMouseState().Position.X > guipropio->boton.at(3)->posicionX && receiver.GetMouseState().Position.X < guipropio->boton.at(3)->posicionX + 240)
                            {


                                options = false;
                            }

                        }
                        else if(receiver.GetMouseState().Position.Y > guipropio->control.at(0)->posicionY && receiver.GetMouseState().Position.Y < guipropio->control.at(0)->posicionY + 90)
                        {
                            if(receiver.GetMouseState().Position.X > guipropio->control.at(0)->posicionX && receiver.GetMouseState().Position.X < guipropio->control.at(0)->posicionX + 130)
                            {
                                if(volumen > 0)
                                {
                                    guipropio->control.at(0)->menos();
                                    volumen = volumen - 0.1;
                                }
                            }
                            else if(receiver.GetMouseState().Position.X > guipropio->control.at(0)->posicionX + 130 && receiver.GetMouseState().Position.X < guipropio->control.at(0)->posicionX + 260)
                            {
                                if(volumen < 1)
                                {
                                    guipropio->control.at(0)->mas();
                                    volumen = volumen + 0.1;
                                }
                            }
                        }
                        else if(receiver.GetMouseState().Position.Y > guipropio->titulo.at(1)->posicionY && receiver.GetMouseState().Position.Y < guipropio->titulo.at(1)->posicionY + 50)
                        {
                            if(receiver.GetMouseState().Position.X > guipropio->titulo.at(1)->posicionX && receiver.GetMouseState().Position.X < guipropio->titulo.at(1)->posicionX + 200)
                            {
                                opcionesresolucion = true;

                            }
                        }
                    }
                }
                else
                {
                    guipropio->control.at(1)->draw(driver);

                    if(receiver.GetMouseState().LeftButtonDown)
                    {
                        if(receiver.GetMouseState().Position.X > guipropio->control.at(1)->posicionX+10 && receiver.GetMouseState().Position.X < guipropio->control.at(1)->posicionX + 200)
                        {
                            if(receiver.GetMouseState().Position.Y > guipropio->control.at(1)->posicionY+10 && receiver.GetMouseState().Position.Y < guipropio->control.at(1)->posicionY + 41.25)
                            {
                                guipropio->control.at(1)->a = true;
                                guipropio->control.at(1)->b = false;
                                guipropio->control.at(1)->c = false;
                                guipropio->control.at(1)->d = false;
                                resolucionX = 1360;
                                resolucionY = 768;

                            }
                            else if(receiver.GetMouseState().Position.Y > guipropio->control.at(1)->posicionY+41.25 && receiver.GetMouseState().Position.Y < guipropio->control.at(1)->posicionY + 72.50)
                            {
                                guipropio->control.at(1)->a = false;
                                guipropio->control.at(1)->b = true;
                                guipropio->control.at(1)->c = false;
                                guipropio->control.at(1)->d = false;
                                resolucionX = 1280;
                                resolucionY = 720;

                            }
                            else if(receiver.GetMouseState().Position.Y > guipropio->control.at(1)->posicionY+72.50 && receiver.GetMouseState().Position.Y < guipropio->control.at(1)->posicionY + 103.75)
                            {
                                guipropio->control.at(1)->a = false;
                                guipropio->control.at(1)->b = false;
                                guipropio->control.at(1)->c = true;
                                guipropio->control.at(1)->d = false;
                                resolucionX = 1024;
                                resolucionY = 768;

                            }
                            else if(receiver.GetMouseState().Position.Y > guipropio->control.at(1)->posicionY+103.75 && receiver.GetMouseState().Position.Y < guipropio->control.at(1)->posicionY + 135)
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
                        else
                            opcionesresolucion = false;

                    }
                }

            }


            driver->endScene();
        }
    }

    MenuDevice->drop();





    return start;
}
