#ifndef TENTIDAD_H
#define TENTIDAD_H

#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stack>

using namespace glm;
using namespace std;

class TEntidad
{
    public:
        TEntidad();
        virtual ~TEntidad();

        //virtual pura
        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;



    protected:
        static stack<mat4> pila;

    private:

};

#endif // TENTIDAD_H
