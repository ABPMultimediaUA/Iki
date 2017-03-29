#ifndef HUD_ELEMENT_H
#define HUD_ELEMENT_H

#include "Structs.h"

class Image;

class HUD_Element
{
    public:
        HUD_Element(int, int, Structs::TRectangulo, std::string, bool);
        ~HUD_Element();

        void draw();
        void cambiarRect(Structs::TRectangulo);
        bool comprobarEncima();
        void setActive(bool);
        bool isActive(){return active;}

    protected:

    private:
        Image* imagen;
        int posicionX, posicionY;
        Structs::TRectangulo rec;
        Structs::TColor color;
        bool active;

};

#endif // HUD_ELEMENT_H
