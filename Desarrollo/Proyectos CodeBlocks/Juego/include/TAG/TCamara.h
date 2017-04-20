#ifndef TCAMARA_H
#define TCAMARA_H

#include <iostream>
#include <vector>

#include <TAG/TEntidad.h>


class TCamara : public TEntidad
{
    public:
        TCamara(const vec3& pos, float grad, int anch, int alt, float cer, float lej);
        virtual ~TCamara();

        void setPerspectiva(float grad, int anch, int alt, float cer, float lej);
        void setParalela(float izq, float dch, float inf, float sup, float cer, float lej);
        mat4 getMatrizProyeccion() const;
        void beginDraw();
        void endDraw();

    protected:

    private:
        bool esPerspectiva;
        float superior, inferior, izquierda, derecha, cercano, lejano, ancho, alto, viewpoint;
        mat4 m_perspectiva, m_paralela;
        vec3 v_posicion;
};

#endif // TCAMARA_H
