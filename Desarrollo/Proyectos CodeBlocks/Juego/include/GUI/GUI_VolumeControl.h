#ifndef GUI_VOLUMECONTROL_H
#define GUI_VOLUMECONTROL_H

#include "GUI_Component.h"


class GUI_VolumeControl : public GUI_Component
{
    public:
        GUI_VolumeControl();
        ~GUI_VolumeControl();

        void draw();

    protected:

    private:
        Image* image2;
        Structs::TRectangulo rec2;
        int posicionX2, posicionY2;
        int porcentajeVol;
};

#endif // GUI_VOLUMECONTROL_H
