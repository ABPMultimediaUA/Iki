// This is a Demo of the Irrlicht Engine (c) 2005-2009 by N.Gebhardt.
// This file is not documented.

#include "CMainMenu.h"



CMainMenu::CMainMenu()
: startButton(0), salirButton(0), MenuDevice(0), start(false)
{
}



bool CMainMenu::run()
{


	MenuDevice = createDevice(video::EDT_OPENGL,core::dimension2d<u32>(1360, 768), 16, false, false, false, this);


	video::IVideoDriver* driver = MenuDevice->getVideoDriver();
	scene::ISceneManager* smgr = MenuDevice->getSceneManager();
	gui::IGUIEnvironment* guienv = MenuDevice->getGUIEnvironment();

	core::stringw str = "Irrlicht Engine Demo v";
	str += MenuDevice->getVersion();
	MenuDevice->setWindowCaption(str.c_str());

	// set new Skin
	gui::IGUISkin* newskin = guienv->createSkin(gui::EGST_BURNING_SKIN);
	guienv->setSkin(newskin);
	newskin->drop();


	// add images

	const s32 leftX = 550;

	// add tab control

	gui::IGUITabControl* tabctrl = guienv->addTabControl(core::rect<int>(leftX,100,800-10,768-10),
		0, false, false);


	// add list box


	startButton = guienv->addButton(core::rect<int>(30,195,200,224), tabctrl, 2, L"Nueva Partida");
	salirButton = guienv->addButton(core::rect<int>(30,295,200,324), tabctrl, 3, L"Salir");



	// create a fixed camera
	smgr->addCameraSceneNode(0, core::vector3df(45,0,0), core::vector3df(0,0,0));



	while(MenuDevice->run())
	{
		if (MenuDevice->isWindowActive())
		{
			driver->beginScene(false, true, video::SColor(0,0,0,0));




			smgr->drawAll();
			guienv->drawAll();
			driver->endScene();
		}
	}

	MenuDevice->drop();





	return start;
}


bool CMainMenu::OnEvent(const SEvent& event)
{

	if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID();
		switch(id)
		{
		case 2:
			if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED )
			{
				MenuDevice->closeDevice();
				start = true;
			}
		case 3:
			if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED )
				MenuDevice->closeDevice();

		}
	}

	return start;
}


