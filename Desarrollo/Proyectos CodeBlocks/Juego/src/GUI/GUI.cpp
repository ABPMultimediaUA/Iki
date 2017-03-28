#include "GUI/GUI.h"
#include "GUI/GUI_Button.h"
#include "GUI/GUI_Menu.h"
#include "GUI/GUI_Title.h"
#include "GUI/GUI_Control.h"
#include "GUI/GUI_VolumeControl.h"
#include "Fachada/GraphicsFacade.h"

GUI::GUI()
{
    //ctor
}

GUI::~GUI()
{
    //dtor
}

void GUI::anyadirmenu(int x, int y){
    componentes.push_back(new GUI_Menu(x, y));
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

    componentes[0]->draw();
    if(draw_type == 1){
        componentes[1]->draw();
        componentes[2]->draw();
        componentes[3]->draw();
    }
    else if(draw_type == 2 || draw_type == 3 || draw_type == 4){
        componentes[5]->draw();
        componentes[10]->draw();
        componentes[6]->draw();
        componentes[4]->draw();
        if(draw_type == 2)
            componentes[7]->draw();
        else if(draw_type == 3)
            componentes[9]->draw();
        else if(draw_type == 4){
            componentes[7]->draw();
            componentes[8]->draw();
        }
    }
}

void GUI::clean(){
    componentes.clear();
}
