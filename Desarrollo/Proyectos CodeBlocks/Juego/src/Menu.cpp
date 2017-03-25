#include "Menu.h"
#include "GUI/GUI.h"
#include "GUI_Button.h"
#include "GUI_Title.h"
#include "GUI_Control.h"
#include "GUI_VolumeControl.h"
#include "Fachada/GraphicsFacade.h"

Menu::Menu()
{
    gui = new GUI();

    volumen = 0.5;

    draw_type = 0;
}

Menu::~Menu()
{
    //dtor
}

void Menu::inicializar_menu(){
    ///MENU
    gui->anyadirmenu (400, 60);

    ///BOTONES
    gui->anyadirboton(540, 160, "nuevapartidaboton");
    NuevaPartida = static_cast<GUI_Button*>(gui->getComponentes().back());

    gui->anyadirboton(540, 440, "salirboton");
    Salir        = static_cast<GUI_Button*>(gui->getComponentes().back());

    gui->anyadirboton(540, 300, "botonopciones");
    Opciones     = static_cast<GUI_Button*>(gui->getComponentes().back());

    gui->anyadirboton(540, 540, "botonatras");
    Atras        = static_cast<GUI_Button*>(gui->getComponentes().back());

    ///TITULOS
    gui->anyadirtitulo(570, 125, "titulovolumen");

    gui->anyadirtitulo(570, 270, "resolucionboton");
    Resolucion        = static_cast<GUI_Title*>(gui->getComponentes().back());

    gui->anyadirtitulo(570, 340, "controlestitulo");
    Control_Tit       = static_cast<GUI_Title*>(gui->getComponentes().back());

    gui->anyadirtitulo(565, 390, "controlespanel");
    gui->getComponentes().back()->setRect(214, 145);

    ///CONTROLES

    gui->anyadircontrol(565, 320, "resoluciondentro", "checklleno");
    Controles         = static_cast<GUI_Control*>(gui->getComponentes().back());

    ///CONTROL VOLUMEN

    gui->anyadirvolumen(540, 175);
    Volumen           = static_cast<GUI_VolumeControl*>(gui->getComponentes().back());

}

void Menu::comprobarBotones(){
    NuevaPartida->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);
    Opciones->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);
    Salir->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);
    Atras->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);
    Resolucion->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);
    Control_Tit->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);
}

bool Menu::run(){

    while(GraphicsFacade::getInstance().run()){

        gui->draw(draw_type);

        comprobarBotones();

        if(MyEventReceiver::getInstance().GetMouseState().LeftButtonDown){
            if(draw_type == 0){
                if(NuevaPartida->getActivo()){
                    return true;
                }
                else if(Opciones->getActivo()){
                    draw_type = 1;
                }
                else if(Salir->getActivo()){
                    GraphicsFacade::getInstance().close();
                    return true;
                    exit(0);
                }
            }
            else if(draw_type == 1){
                Volumen->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);

                if(Resolucion->getActivo())
                    draw_type = 2;
                else if(Control_Tit->getActivo())
                    draw_type = 3;
                else if(Atras->getActivo())
                    draw_type = 0;
            }
            else if(draw_type == 2){
                GraphicsFacade::getInstance().changeResolution(Controles->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y));

                if(Resolucion->getActivo())
                    draw_type = 1;
            }
            else if(draw_type == 3){
                    if(Control_Tit->getActivo())
                    draw_type = 1;
            }
        }
    }
    return false;
}
