#include "Menu.h"
#include "GUI/GUI.h"
#include "GUI/GUI_Button.h"
#include "GUI/GUI_Title.h"
#include "GUI/GUI_Control.h"
#include "GUI/GUI_VolumeControl.h"
#include "Fachada/GraphicsFacade.h"
#include "SoundManager.h"

Menu::Menu()
{
    //gui = new GUI();
    time_since_clicked = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
    draw_type = 1;
}

Menu::~Menu()
{
    //dtor
}

void Menu::cargarSonidos()
{
    SoundMgr->cargarSonido("Menu/menu_alante");
    SoundMgr->cargarSonido("Menu/menu_alante2");
    SoundMgr->cargarSonido("Menu/menu_atras");
    SoundMgr->cargarMusica("Musica/menu_musica");
}

void Menu::inicializar_menu(int menu){

    GraphicsFacade::getInstance().inicializar_gui(menu);
    GUI* gui = GraphicsFacade::getInstance().getGUI();

    cargarSonidos();

    ///MENU
    //gui->anyadirmenu (400, 60);

    ///BOTONES
    //if(menu == 0)
    //    gui->anyadirboton(540, 160, "nuevapartidaboton");
    //else
    //    gui->anyadirboton(540, 160, "botoncontinuar");
    NuevaPartida = static_cast<GUI_Button*>(gui->getComponentes()[1]);

    //gui->anyadirboton(540, 440, "salirboton");
    Salir        = static_cast<GUI_Button*>(gui->getComponentes()[2]);

    //gui->anyadirboton(540, 300, "botonopciones");
    Opciones     = static_cast<GUI_Button*>(gui->getComponentes()[3]);

    //gui->anyadirboton(540, 540, "botonatras");
    Atras        = static_cast<GUI_Button*>(gui->getComponentes()[4]);

    ///TITULOS
    //gui->anyadirtitulo(570, 125, "titulovolumen");

    //gui->anyadirtitulo(570, 270, "resolucionboton");
    Resolucion        = static_cast<GUI_Title*>(gui->getComponentes()[6]);

    //gui->anyadirtitulo(570, 340, "controlestitulo");
    Control_Tit       = static_cast<GUI_Title*>(gui->getComponentes()[7]);

    //gui->anyadirtitulo(565, 390, "controlespanel");
    gui->getComponentes()[8]->setRect(214, 145);

    ///CONTROLES

    //gui->anyadircontrol(565, 320, "resoluciondentro", "checklleno");
    Controles         = static_cast<GUI_Control*>(gui->getComponentes()[9]);

    ///CONTROL VOLUMEN

    //gui->anyadirvolumen(540, 175);
    Volumen           = static_cast<GUI_VolumeControl*>(gui->getComponentes()[10]);

}

void Menu::comprobarBotones(int draw_type){
    if(draw_type == 1){
        NuevaPartida->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);
        Opciones->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);
        Salir->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);
    }else if(draw_type == 2)
        Atras->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);
    if(draw_type == 2 || draw_type == 3 || draw_type == 4){
        Resolucion->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);
        Control_Tit->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);
    }
}

bool Menu::run(int ingame){

    draw_type = 1;
    SoundMgr->playMusica("Musica/menu_musica");

    while(GraphicsFacade::getInstance().run()){

        GraphicsFacade::getInstance().draw(draw_type);

        comprobarBotones(draw_type);

        if(MyEventReceiver::getInstance().GetMouseState().LeftButtonDown){
            if(GraphicsFacade::getInstance().getTimer()->getTime()/1000.f - time_since_clicked > 0.2){
                if(draw_type == 1){
                    if(NuevaPartida->getActivo()){
                        NuevaPartida->reproducir_click(0);
                        GraphicsFacade::getInstance().vaciar_gui(ingame);
                        SoundMgr->soundStop("Musica/menu_musica");
                        return true;
                    }
                    else if(Opciones->getActivo()){
                        Opciones->reproducir_click(0);
                        draw_type = 2;
                    }
                    else if(Salir->getActivo()){
                        Salir->reproducir_click(1);
                        GraphicsFacade::getInstance().close();
                        return true;
                        exit(0);
                    }
                }
                else if(draw_type == 2){
                    Volumen->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y);

                    if(Resolucion->getActivo()){
                        Resolucion->reproducir_click(0);
                        draw_type = 3;
                    }
                    else if(Control_Tit->getActivo()){
                        Control_Tit->reproducir_click(0);
                        draw_type = 4;
                    }
                    else if(Atras->getActivo()){
                        Atras->reproducir_click(1);
                        draw_type = 1;
                    }
                }
                else if(draw_type == 3){
                    //GraphicsFacade::getInstance().changeResolution(Controles->comprobarmouse(MyEventReceiver::getInstance().GetMouseState().Position.X, MyEventReceiver::getInstance().GetMouseState().Position.Y));

                    if(Resolucion->getActivo()){
                        Resolucion->reproducir_click(0);
                        draw_type = 2;
                    }
                }
                else if(draw_type == 4){
                    if(Control_Tit->getActivo()){
                        Control_Tit->reproducir_click(0);
                        draw_type = 2;
                    }
                }
                time_since_clicked = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
            }
        }
    }
    return false;
}
