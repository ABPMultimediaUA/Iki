#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

class Image;

class GUI_Button
{
    public:
        GUI_Button(int, int, int);
        ~GUI_Button();

        bool getActivo(){return estaencima;}
        void draw();
        void comprobarmouse(float, float);

    protected:

    private:
        Image* image;
        int posicionX, posicionY;
        bool estaencima;
};

#endif // GUI_BUTTON_H
