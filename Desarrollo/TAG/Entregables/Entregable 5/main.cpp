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

    //Transladamos la matriz (5, 5, 5)
    cout<<"Transladamos la matriz (5, 5, 5): "<<endl;
    transform0->trasladar(5.0f, 5.0f, 5.0f);

    //Rotamos la matriz en el eje x 45º
    cout<<"Rotamos la matriz en el eje x 45º: "<<endl;
    transform1->rotar(45.0f, 1.0f, 0.0f, 0.0f);

    //Rotamos la matriz en el eje y 45º
    cout<<"Rotamos la matriz en el eje y 45º: "<<endl;
    transform2->rotar(45.0f, 0.0f, 1.0f, 0.0f);

    //Rotamos la matriz en el eje z 45º
    cout<<"Rotamos la matriz en el eje z 45º: "<<endl;
    transform3->rotar(45.0f, 0.0f, 0.0f, 1.0f);

    cout<<"Escalamos la matriz (5): "<<endl;
    transform4->escalarAbs(5.0f);

    cout<<"Escalamos la matriz (2, 3, 6): "<<endl;
    transform5->escalarRel(2.0f, 3.0f, 6.0f);

    cout<<""<<endl;
    cout<<""<<endl;



    std::cin>>x;

    return 0;
}
