#include "TNodo.h"
#include "TTransform.h"

#define WIDTH 800
#define HEIGHT 600

using namespace std;


int main(int argc, char *argv[])
{
    int x;
    TNodo* noditoEsc= new TNodo("Root");
    TNodo* nodito0= new TNodo("nod0");
    TNodo* nodito1= new TNodo("nod1");
    TNodo* nodito2= new TNodo("nod2");
    TNodo* nodito3= new TNodo("nod3");
    TNodo* nodito4= new TNodo("nod4");
    TNodo* nodito5= new TNodo("nod5");
    TNodo* nodito6= new TNodo("nod6");
    TNodo* nodito7= new TNodo("nod7");
    TNodo* nodito8= new TNodo("nod8");
    TNodo* nodito9= new TNodo("nod9");

    TTransform* transform0 = new TTransform();
    TTransform* transform1 = new TTransform();
    TTransform* transform2 = new TTransform();
    TTransform* transform3 = new TTransform();
    TTransform* transform4 = new TTransform();
    TTransform* transform5 = new TTransform();
    TTransform* transform6 = new TTransform();
    TTransform* transform7 = new TTransform();
    TTransform* transform8 = new TTransform();

    nodito0->setEntidad(transform0);
    nodito1->setEntidad(transform1);


    nodito0->setEntidad(nullptr);
    nodito1->setEntidad(nullptr);
    nodito2->setEntidad(nullptr);
    nodito3->setEntidad(nullptr);
    nodito4->setEntidad(nullptr);
    nodito5->setEntidad(nullptr);
    nodito6->setEntidad(nullptr);
    nodito7->setEntidad(nullptr);
    nodito8->setEntidad(nullptr);
    nodito9->setEntidad(nullptr);

    noditoEsc->addHijo(nodito0);
    noditoEsc->addHijo(nodito1);
    noditoEsc->addHijo(nodito2);

    nodito0->addHijo(nodito3);
    nodito0->addHijo(nodito4);

    nodito1->addHijo(nodito5);

    nodito2->addHijo(nodito6);

    nodito3->addHijo(nodito7);
    nodito3->addHijo(nodito8);

    nodito5->addHijo(nodito9);


    noditoEsc->draw();

    std::cin>>x;

    return 0;
}
