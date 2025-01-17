#ifndef MENU_H
#define MENU_H

#include "Structs.h"

class GUI;
class GUI_Button;
class GUI_Title;
class GUI_Control;
class GUI_VolumeControl;

class Menu
{
    public:
        Menu();
        ~Menu();

        void cargarSonidos();
        void inicializar_menu(int);
        void draw();
        void comprobarBotones(int);
        bool run();

    protected:

    private:

        //GUI* gui;
        GUI_Button* NuevaPartida;
        GUI_Button* Opciones;
        GUI_Button* Salir;
        GUI_Button* Atras;

        GUI_Title* Resolucion;
        GUI_Title* Control_Tit;

        GUI_Control* Controles;

        GUI_VolumeControl* Volumen;

        int draw_type; //0-> Menu por defecto; 1-> Menu opciones; 2-> Menu con resolucion; 3-> Menu con controles
        f32 time_since_clicked;
};

#endif // MENU_H
