#ifndef TCAMARA_H
#define TCAMARA_H

#include <iostream>
#include <vector>

#include <TEntidad.h>


class TCamara : public TEntidad
{
    public:
        TCamara();
        virtual ~TCamara();

        void setPerspectiva(float sup, float inf, float izq, float dch, float cer, float lej);
        void setParalela(float sup, float inf, float izq, float dch, float cer, float lej);

        void beginDraw();
        void endDraw();

    protected:

    private:
        bool esPerspectiva;
        float superior, inferior, izquierda, derecha, cercano, lejano;
};

#endif // TCAMARA_H
