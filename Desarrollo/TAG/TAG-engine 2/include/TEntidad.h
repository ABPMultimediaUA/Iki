#ifndef TENTIDAD_H
#define TENTIDAD_H

#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL\glew.h>
#include <GL/gl.h>

#include <stack>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
        static mat4 ms_gmatriz;
        static stack<mat4> pila;

    private:

};

#endif // TENTIDAD_H
