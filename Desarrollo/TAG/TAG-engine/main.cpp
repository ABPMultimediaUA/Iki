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
    TNodo* noditoEsc= new TNodo();
    TNodo* nodito0= new TNodo();
    TNodo* nodito1= new TNodo();
    TNodo* nodito2= new TNodo();
    TNodo* nodito3= new TNodo();
    TNodo* nodito4= new TNodo();
    TNodo* nodito5= new TNodo();
    TNodo* nodito6= new TNodo();
    TNodo* nodito7= new TNodo();
    TNodo* nodito8= new TNodo();
    TNodo* nodito9= new TNodo();
    TNodo* nodito10= new TNodo();
    TNodo* nodito11= new TNodo();
    TNodo* nodito12= new TNodo();
    TNodo* nodito13= new TNodo();
    TNodo* nodito14= new TNodo();
    TNodo* nodito15= new TNodo();

//Transformaciones
    TTransform* transformEsc= new TTransform();
    TTransform* transform0= new TTransform();
    TTransform* transform1= new TTransform();
    TTransform* transform2= new TTransform();
    TTransform* transform3= new TTransform();
    TTransform* transform4= new TTransform();
    TTransform* transform5= new TTransform();

    //noditoEsc->setEntidad(transformEsc);
    nodito0->setEntidad(transform0);
    nodito1->setEntidad(transform1);
    nodito2->setEntidad(transform2);
    nodito3->setEntidad(transform3);
    nodito4->setEntidad(transform4);
    nodito9->setEntidad(transform5);

//Camaras
    TCamara* camara0= new TCamara();
    TCamara* camara1= new TCamara();

    nodito5->setEntidad(camara0);
    nodito12->setEntidad(camara1);

//Luces

    TLuz* luz0= new TLuz();
    TLuz* luz1= new TLuz();
    TLuz* luz2= new TLuz();

    nodito6->setEntidad(luz0);
    nodito7->setEntidad(luz1);
    nodito8->setEntidad(luz2);

//Mallas
    TMalla* malla0= new TMalla();
    TMalla* malla1= new TMalla();
    TMalla* malla2= new TMalla();
    TMalla* malla3= new TMalla();
    TMalla* malla4= new TMalla();

    nodito10->setEntidad(malla0);
    nodito11->setEntidad(malla1);
    nodito13->setEntidad(malla2);
    nodito14->setEntidad(malla3);
    nodito15->setEntidad(malla4);

//Creamos el arbol

////// Hijos de Escena
    noditoEsc->addHijo(nodito0);
    noditoEsc->addHijo(nodito1);
    noditoEsc->addHijo(nodito2);
    noditoEsc->addHijo(nodito3);
////// Hijos de N0
    nodito0->addHijo(nodito4);
    nodito0->addHijo(nodito5);

    nodito4->addHijo(nodito12);
////// Hijos de N1
    nodito1->addHijo(nodito6);
    nodito1->addHijo(nodito7);
    nodito1->addHijo(nodito8);
////// Hijos de N2
    nodito2->addHijo(nodito9);

    nodito9->addHijo(nodito13);
    nodito9->addHijo(nodito14);
    nodito9->addHijo(nodito15);
////// Hijos de N3
    nodito3->addHijo(nodito10);
    nodito3->addHijo(nodito11);
//////

    noditoEsc->draw();


    return 0;
}
