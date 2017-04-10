#include "GUI/GUI.h"
#include "GUI/GUI_Button.h"
#include "GUI/GUI_Menu.h"
#include "GUI/GUI_Title.h"
#include "GUI/GUI_Control.h"
#include "GUI/GUI_VolumeControl.h"
#include "Fachada/GraphicsFacade.h"
#include "GUI/HUD.h"

GUI::GUI()
{
}

GUI::~GUI()
{
}

void GUI::anyadirmenu(int x, int y, int t){
    componentes.push_back(new GUI_Menu(x, y, t));
}

void GUI::anyadirboton(int x, int y, std::string nombre){
    componentes.push_back(new GUI_Button(x, y, nombre));
}

void GUI::anyadirtitulo(int x, int y, std::string nombre){
    componentes.push_back(new GUI_Title(x, y, nombre));
}

void GUI::anyadircontrol(int x, int y, std::string nombre, std::string nombre2){
    componentes.push_back(new GUI_Control(x, y, nombre, nombre2));
}

void GUI::anyadirvolumen(int x, int y){
    componentes.push_back(new GUI_VolumeControl(x, y));
}

void GUI::draw(int draw_type){

    if(draw_type == 0)
        HUD::getInstance()->draw();
    else{
        componentes[0]->draw();
        componentes[1]->draw();
    }
    if(draw_type == 1){
        componentes[2]->draw();
        componentes[3]->draw();
        componentes[4]->draw();
    }
    else if(draw_type == 2 || draw_type == 3 || draw_type == 4){
        componentes[6]->draw();
        componentes[11]->draw();
        componentes[7]->draw();
        componentes[5]->draw();
        if(draw_type == 2)
            componentes[8]->draw();
        else if(draw_type == 3)
            componentes[10]->draw();
        else if(draw_type == 4){
            componentes[8]->draw();
            componentes[9]->draw();
        }
    }
}

void GUI::clean(){
    componentes.clear();
}

void GUI::inicializar_hd(){
    HUD::getInstance()->inicializar_HUD();
}
