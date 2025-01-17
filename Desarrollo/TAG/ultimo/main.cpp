#include "TDisplay.h"
#include "TMotorTAG.h"
#include "TShader.h"



using namespace std;

int main(int argc, char *argv[])
{
    TDisplay display(800, 600,"Motor grafico");

    TMotorTAG  *motor   = new TMotorTAG();

    TNodo *nCamara = motor->crearCamara(glm::vec3(0, 0, 10), 45.0f, 800, 600, 0.1f, 1000.0f);
    TCamara *cCamara = dynamic_cast<TCamara*>(nCamara->getEntidad());


    int iCamara = motor->registrarCamara(nCamara);
    motor->setCamaraActiva(iCamara);


    ///Escena
    ///     |---nodoTransf1---nodoLuz1
    ///     |
    ///     |---nodoTransf2---nodoTransf5--nodoMalla1
    ///     |             |---nodoTransf6
    ///     |
    ///     |---nodoTransf3---nodoTransf4---nodoCamara1


    //TNodo *nodoMalla = motor->crearMalla("./res/cube2.obj");
    TShader shader = motor->cargarShader("./res/basicShader");
    TNodo *nodoAnimacion = motor->cargarAnimacion("./res/animacion/mini_knight_fem_",20);






    while(!display.IsClosed())
    {
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

        shader.Bind();
        motor->draw();
        shader.Update(cCamara);

		display.Update();
    }



}
