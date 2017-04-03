#ifndef GUI_VOLUMECONTROL_H
#define GUI_VOLUMECONTROL_H

#include "GUI_Component.h"


class GUI_VolumeControl : public GUI_Component
{
    public:
        GUI_VolumeControl(int, int);
        ~GUI_VolumeControl();

        void draw();
        void subirVolumen();
        void bajarVolumen();
        int comprobarmouse(float, float);

    protected:

    private:
        Image* image2;
        Structs::TRectangulo rec2;
        int posicionX2, posicionY2;
        float volumen;
        //int porcentajeVol;
};

#endif // GUI_VOLUMECONTROL_H
