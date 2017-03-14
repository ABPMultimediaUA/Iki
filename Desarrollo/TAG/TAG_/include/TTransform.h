#ifndef TTRANSFORM_H
#define TTRANSFORM_H

#include <iostream>
#include <TEntidad.h>

#include <GL/gl.h>

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

        void beginDraw();
        void endDraw();

    protected:

    private:
        mat4 matriz;


};

#endif // TTRANSFORM_H
