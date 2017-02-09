#ifndef TTRANSFORM_H
#define TTRANSFORM_H

#include <glm.hpp>
#include <TEntidad.h>


using namespace glm;

class TTransform : public TEntidad
{
    public:
        TTransform();
        virtual ~TTransform();

        void identidad();
        void cargar(mat4 matriz);
        void trasponer();
        void trasladar(float x, float y, float z);
        void rotar(float ang, float x, float y, float z);

        void beginDraw();
        void endDraw();

    protected:

    private:
        mat4 matriz;
};

#endif // TTRANSFORM_H
