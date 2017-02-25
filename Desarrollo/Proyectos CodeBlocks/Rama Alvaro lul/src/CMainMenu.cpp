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

	MenuDevice = createDevice(video::EDT_OPENGL,core::dimension2d<u32>(1360, 768), 16, false, false, false, &receiver);


	video::IVideoDriver* driver = MenuDevice->getVideoDriver();
	scene::ISceneManager* smgr = MenuDevice->getSceneManager();
	guilul *guipropio = new guilul;

	core::stringw str = "Irrlicht Engine Demo v";
	str += MenuDevice->getVersion();
	MenuDevice->setWindowCaption(str.c_str());



	while(MenuDevice->run())
	{
		if (MenuDevice->isWindowActive())
		{
			driver->beginScene(false, true, video::SColor(0,0,0,0));

            guipropio->anyadirmenu(400, 60, driver);
            guipropio->anyadirboton(0, 540, 160, driver);
            guipropio->anyadirboton(1, 540, 300, driver);

			if(receiver.GetMouseState().LeftButtonDown){
                if(receiver.GetMouseState().Position.X > 542 && receiver.GetMouseState().Position.X < 778){
                    if(receiver.GetMouseState().Position.Y > 172 && receiver.GetMouseState().Position.Y < 275){
                        MenuDevice->closeDevice();
                        start = true;

                    }
                    else if(receiver.GetMouseState().Position.Y > 304 && receiver.GetMouseState().Position.Y < 414){
                        MenuDevice->closeDevice();
                        exit(0);
                    }
                }
            }


			driver->endScene();
		}
	}

	MenuDevice->drop();





	return start;
}
