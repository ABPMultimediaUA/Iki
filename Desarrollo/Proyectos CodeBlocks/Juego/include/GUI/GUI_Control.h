#ifndef GUI_CONTROL_H
#define GUI_CONTROL_H

#include "GUI_Component.h"

class GUI_Control : public GUI_Component
{
    public:
        GUI_Control(int, int, std::string, std::string);
        ~GUI_Control();

        void draw();
        int comprobarmouse(float, float);

    protected:

    private:
        Image* image2;
        Structs::TRectangulo rec2;
        int posicionX2, posicionY2;
};

#endif // GUI_CONTROL_H
