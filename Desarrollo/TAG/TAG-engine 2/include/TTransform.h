#ifndef TTRANSFORM_H
#define TTRANSFORM_H

#include <iostream>
#include <TEntidad.h>

//#include <GL/gl.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

using namespace glm;
using namespace std;

class TTransform : public TEntidad
{
    public:
        TTransform();
        virtual ~TTransform();

        void identidad();
        void cargar(mat4 mat);
        void trasponer();
        void trasladar(float x, float y, float z);
        void rotar(float angulo, float x, float y, float z);
        mat4 getMatriz(){return matriz;};

        mat4 GetModel() const;

        void beginDraw();
        void endDraw();

    protected:

    private:
        mat4 matriz;
        glm::vec3 m_pos;
        glm::vec3 m_rot;
        glm::vec3 m_scale;


};

#endif // TTRANSFORM_H
