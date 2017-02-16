#include <iostream>

#include <glm.hpp>
#include <GL/gl.h>

#include "TNodo.h"
#include "TTransform.h"
#include "TLuz.h"
#include "TMalla.h"
#include "TCamara.h"

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    TNodo* noditoEsc= new TNodo();
    TNodo* nodito0= new TNodo();
    TNodo* nodito1= new TNodo();
    TNodo* nodito2= new TNodo();

    TMalla* malla0= new TMalla();
    TTransform* transform0 = new TTransform();
    TTransform* transform1 = new TTransform();

    nodito0->setEntidad(transform0);
    nodito1->setEntidad(transform1);
    nodito2->setEntidad(malla0);

    noditoEsc->addHijo(nodito0);
    nodito0->addHijo(nodito1);
    nodito1->addHijo(nodito2);

    transform0->rotar(90, 5, 5, 5);
    transform1->trasladar(10, 10, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    noditoEsc->draw();

    return 0;
}
