#ifndef TCAMARA_H
#define TCAMARA_H

#include <TEntidad.h>


class TCamara : public TEntidad
{
    public:
        TCamara();
        virtual ~TCamara();

        void setPerspectiva(float x, float y);
        void setParalela(float x, float y);

        void beginDraw();
        void endDraw();

    protected:

    private:
        bool esPerspectiva;
        float cercano, lejano;
};

#endif // TCAMARA_H
