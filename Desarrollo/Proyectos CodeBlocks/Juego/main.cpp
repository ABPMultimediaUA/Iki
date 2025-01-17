#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

//#include <irrKlang.h>
#include "lib/irrKlang/conio.h"
#include "Game.h"
#include <iostream>


#include "TDisplay.h"
#include "TMotorTAG.h"
#include "TShader.h"

#include "TEventReceiver.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*TDisplay display(1360, 768,"Motor grafico");

    TMotorTAG  *motor   = new TMotorTAG();

    TNodo *nCamara = motor->crearCamara(glm::vec3(0, 0, 10), 72.0f, 1360, 768, 1.f, 3000.0f);
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


    TNodo *nodoMalla = motor->crearMalla("./resources/res/cube2.obj");
    TShader shader = motor->cargarShader("./resources/res/basicShader");
    TNodo *nodoAnimacion = motor->cargarAnimacion("./resources/res/animacion/mini_knight_fem_",20);


    EVENTO evnt;




    while(!display.IsClosed())
    {
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

        while(ON_EVENT(&evnt))
        {
            switch(evnt.type)
            {
                case KPULSADA:
                    //std::cout<<"Pulso la tecla tt "<<std::endl;
                break;

                case KNO_PULSADA:
                    //std::cout<<"No pulsada"<<std::endl;
                break;

                default:
                break;
            }
        }

        shader.Bind();
        motor->draw();
        shader.Update(cCamara);

		display.Update();
    }
*/
    Game* game = new Game();
    game->start_game();

}
