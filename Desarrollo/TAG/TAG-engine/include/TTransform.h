#ifndef TTRANSFORM_H
#define TTRANSFORM_H


#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <TEntidad.h>


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
        void rotar(float orient, float x, float y, float z);

        void beginDraw();
        void endDraw();

    protected:

    private:
        mat4 matriz;
};

#endif // TTRANSFORM_H
