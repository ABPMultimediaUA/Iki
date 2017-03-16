#ifndef GUI_H
#define GUI_H

#include <vector>

class GUI_Button;
class GUI_Menu;
class GUI_Control;
class GUI_Title;

class GUI
{
    public:
        GUI();
        ~GUI();

        std::vector<GUI_Button*> getBotones(){return boton;}
        void anyadirboton(int t, int x, int y);

    protected:

    private:

        std::vector<GUI_Button*> boton;
        std::vector<GUI_Menu*> menu;
        std::vector<GUI_Control*> control;
        std::vector<GUI_Title*> titulo;

};

#endif // GUI_H
