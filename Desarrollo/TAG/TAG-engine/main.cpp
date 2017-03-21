#include "TDisplay.h"
#include "TMotorTAG.h"
#include "TShader.h"


using namespace std;

int main(int argc, char *argv[])
{
    TDisplay display(800, 600,"Motor grafico");

    TMotorTAG  *motor   = new TMotorTAG();

    //Transform
    TTransform *transf1 = motor->crearTransform();
    TTransform *transf2 = motor->crearTransform();
    TTransform *transf3 = motor->crearTransform();
    TTransform *transf4 = motor->crearTransform();
    TTransform *transf5 = motor->crearTransform();
    TTransform *transf6 = motor->crearTransform();

    //transf1->trasladar (0.0f, 0.0f, 15.0f);
    //transf2->trasladar (1.0f, 1.0f, 1.0f);
    transf3->trasladar (0.0f, 0.0f, 10.0f);
    //transf4->rotar (90.0f, 1.0f, 0.0f, 0.0f);

    TNodo *nodoTransf1 = motor->crearNodo (motor->getEscena(), transf1);
    TNodo *nodoTransf2 = motor->crearNodo (motor->getEscena(), transf2);
    TNodo *nodoTransf3 = motor->crearNodo (motor->getEscena(), transf3);
    TNodo *nodoTransf4 = motor->crearNodo (nodoTransf3, transf4);
    TNodo *nodoTransf5 = motor->crearNodo (nodoTransf2, transf5);
    TNodo *nodoTransf6 = motor->crearNodo (nodoTransf2, transf6);

    //Luces y Camaras
    TLuz      *luz1    = motor->crearLuz();
    TCamara   *camara1 = motor->crearCamara(glm::vec3(0, 0, 15), 45.0f, 800, 600, 0.1f, 1000.0f);

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
    ///     |---nodoTransf2---nodoTransf5--nodoMalla1
    ///     |             |---nodoTransf6
    ///     |
    ///     |---nodoTransf3---nodoTransf4---nodoCamara1


    TMalla *malla = motor->crearMalla("./res/monkey3.obj");
    TShader shader = motor->cargarShader("./res/basicShader");

    TNodo *nodoMalla1 = motor->crearNodo (nodoTransf5, malla);


    while(!display.IsClosed())
    {
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

        shader.Bind();
        motor->draw();
        shader.Update(camara1);

		display.Update();
    }



}
