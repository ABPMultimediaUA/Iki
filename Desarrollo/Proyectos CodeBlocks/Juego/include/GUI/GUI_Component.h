#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

#include "Structs.h"
class Image;

class GUI_Component
{
    public:
        GUI_Component(){};
        ~GUI_Component();

        bool getActivo(){return estaencima;}
        int getPosX(){return posicionX;}
        virtual void draw();
        virtual int comprobarmouse(float, float);
        void setRect(int,int);

    protected:
        Image* image;
        int posicionX, posicionY;
        bool estaencima;
        Structs::TRectangulo rec;

    private:
};

#endif // GUI_COMPONENT_H
