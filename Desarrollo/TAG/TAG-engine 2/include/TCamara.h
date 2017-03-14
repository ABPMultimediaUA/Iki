#ifndef TCAMARA_H
#define TCAMARA_H

#include <iostream>
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include <TEntidad.h>

using namespace glm;


class TCamara : public TEntidad
{
    public:
        TCamara(const vec3& pos, float fov, float aspect, float cer, float lej);

        virtual ~TCamara();

        void setPerspectiva(float sup, float inf, float izq, float dch, float cer, float lej);
        void setParalela(float sup, float inf, float izq, float dch, float cer, float lej);

        mat4 getViewProjection() const;

        void beginDraw();
        void endDraw();

    protected:

    private:
        bool esPerspectiva;
        float superior, inferior, izquierda, derecha, cercano, lejano;

        mat4 m_perspective;
        vec3 m_position; // posicion de la camara.
};

#endif // TCAMARA_H
