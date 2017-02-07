#include <iostream>

#include "TNodo.h"
#include "TTransform.h"
#include "TLuz.h"
#include "TMalla.h"
#include "TCamara.h"

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    TNodo* nodito1= new TNodo();
    TNodo* nodito2= new TNodo();
    TNodo* nodito3= new TNodo();
    TNodo* nodito4= new TNodo();
    TNodo* nodito5= new TNodo();
    TNodo* nodito6= new TNodo();
    TNodo* nodito7= new TNodo();

//Transformaciones
    TTransform* transform0= new TTransform();
    TTransform* transform1= new TTransform();
    TTransform* transform2= new TTransform();

    nodito1->setEntidad(transform0);

    nodito2->setEntidad(transform1);
    nodito3->setEntidad(transform2);

//Camaras
    TCamara* camara1= new TCamara();
    TCamara* camara2= new TCamara();

    nodito4->setEntidad(camara1);
    nodito5->setEntidad(camara2);

//Luces
    TMalla* malla1= new TMalla();
    TLuz* luz2= new TLuz();

    nodito6->setEntidad(malla1);
    nodito7->setEntidad(luz2);

//Creamos el arbol
    nodito1->addHijo(nodito2);
    nodito1->addHijo(nodito3);

    nodito2->addHijo(nodito4);
    nodito2->addHijo(nodito5);

    nodito3->addHijo(nodito6);
    nodito3->addHijo(nodito7);


    nodito1->draw();


    return 0;
}
