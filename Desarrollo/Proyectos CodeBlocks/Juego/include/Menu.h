#ifndef MENU_H
#define MENU_H

class GUI;

class Menu
{
    public:
        Menu();
        ~Menu();

        bool run();

    protected:

    private:

        GUI* gui;

        float volumen;
        int resolucionX;
        int resolucionY;
};

#endif // MENU_H
