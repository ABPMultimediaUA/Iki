#ifndef GUI_H
#define GUI_H

#include <vector>
#include <string>

class GUI_Component;

class GUI
{
    public:
        GUI();
        ~GUI();

        std::vector<GUI_Component*> getComponentes(){return componentes;}

        void anyadirmenu   (int, int);
        void anyadirboton  (int, int, std::string);
        void anyadirtitulo (int, int, std::string);
        void anyadircontrol(int, int, std::string, std::string);

        void draw(int);

    protected:

    private:

        std::vector<GUI_Component*> componentes;

};

#endif // GUI_H
