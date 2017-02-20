// This is a Demo of the Irrlicht Engine (c) 2005 by N.Gebhardt.
// This file is not documentated.

#ifndef __C_MAIN_MENU_H_INCLUDED__
#define __C_MAIN_MENU_H_INCLUDED__

#include <irrlicht.h>

using namespace irr;

class CMainMenu : public IEventReceiver
{
public:

	CMainMenu();

	bool run();

	virtual bool OnEvent(const SEvent& event);

private:


	gui::IGUIButton* startButton;
	gui::IGUIButton* salirButton;
	IrrlichtDevice *MenuDevice;

	bool start;

	scene::ISceneNode* lightMapNode;
	scene::ISceneNode* dynamicNode;


};

#endif

