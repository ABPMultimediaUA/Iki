#include "TDisplay.h"
#include "TMotorTAG.h"

using namespace std;

int main(int argc, char *argv[])
{
    TMotorTAG  *motor   = new TMotorTAG();

    //Transform
    TTransform *transf1 = motor->crearTransform();
    TTransform *transf2 = motor->crearTransform();
    TTransform *transf3 = motor->crearTransform();
    TTransform *transf4 = motor->crearTransform();
    TTransform *transf5 = motor->crearTransform();
    TTransform *transf6 = motor->crearTransform();

    transf1->trasladar (20,0,5);
    transf2->trasladar (10,10,0);
    transf3->trasladar (0,15,-10);
    transf4->rotar (90,0,0,0);

    TNodo *nodoTransf1 = motor->crearNodo (motor->getEscena(), transf1);
    TNodo *nodoTransf2 = motor->crearNodo (motor->getEscena(), transf2);
    TNodo *nodoTransf3 = motor->crearNodo (motor->getEscena(), transf3);
    TNodo *nodoTransf4 = motor->crearNodo (nodoTransf3, transf4);
    TNodo *nodoTransf5 = motor->crearNodo (nodoTransf2, transf5);
    TNodo *nodoTransf6 = motor->crearNodo (nodoTransf2, transf6);

    //Luces y Camaras
    TLuz      *luz1    = motor->crearLuz();
    TCamara   *camara1 = motor->crearCamara();

    TNodo *nodoLuz1    = motor->crearNodo (nodoTransf1, luz1);
    TNodo *nodoCamara1 = motor->crearNodo (nodoTransf4, camara1);

        //Registro
    int nLuz = motor->registrarLuz(nodoLuz1);
    motor->setLuzActiva(nLuz);

    int nCamara = motor->registrarCamara(nodoCamara1);
    motor->setCamaraActiva(nCamara);

    //Mallas

    ///Escena
    ///     |---nodoTransf1---nodoLuz1
    ///     |
    ///     |---nodoTransf2---nodoTransf5
    ///     |             |---nodoTransf6
    ///     |
    ///     |---nodoTransf3---nodoTransf4---nodoCamara1

    motor->draw();

}
