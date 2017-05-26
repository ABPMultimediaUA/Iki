#ifndef GUI_H
#define GUI_H

#include <vector>
#include <string>

class GUI_Component;
class GUI_Wallpaper;

class GUI
{
    public:
        GUI();
        ~GUI();

        std::vector<GUI_Component*> getComponentes(){return componentes;}

        void anyadirmenu   (int, int, int);
        void anyadirboton  (int, int, std::string);
        void anyadirtitulo (int, int, std::string);
        void anyadircontrol(int, int, std::string, std::string);
        void anyadirvolumen(int, int);
        void anyadirwallpaper(std::string);

        void draw(int);
        void drawCarga(int);
        void clean(int);
        //void inicializar_hd();

    protected:

    private:

        std::vector<GUI_Component*> componentes;
        std::vector<GUI_Wallpaper*> carga;

};

#endif // GUI_H
