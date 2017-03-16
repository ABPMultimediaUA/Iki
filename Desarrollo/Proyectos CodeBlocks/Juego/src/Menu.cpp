#include "Menu.h"
#include "GUI/GUI.h"
#include "GUI_Button.h"
#include "GraphicsFacade.h"

Menu::Menu()
{
    gui = new GUI();

    volumen = 0.5;
    resolucionX = 1360;
    resolucionY = 768;
}

Menu::~Menu()
{
    //dtor
}

bool Menu::run(){

    gui->anyadirboton(0, 540, 160);
    gui->anyadirboton(2, 540, 300);
    gui->anyadirboton(1, 540, 440);

    while(GraphicsFacade::getInstance().run()){
        for(int i = 0; i<=2; i++){
            gui->getBotones().at(i)->draw();
            gui->getBotones().at(i)->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);
        }
        if(MyEventReceiver::getInstance().GetMouseState().LeftButtonDown){
            if(gui->getBotones().at(0)->getActivo()){
                GraphicsFacade::getInstance().drop();
                return true;
            }
            else if(gui->getBotones().at(2)->getActivo()){
                GraphicsFacade::getInstance().drop();
                return true;
                exit(0);
            }
        }
    }
}
