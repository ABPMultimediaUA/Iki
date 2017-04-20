#ifdef _MSC_VER
<<<<<<< HEAD

=======
// We'll define this to stop MSVC complaining about sprintf().
>>>>>>> refs/remotes/origin/master
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

//#include <irrKlang.h>
//#include "lib/irrKlang/conio.h"
#include "Game.h"

#include "TAG/TDisplay.h"
#include "TAG/TMotorTAG.h"
#include "TAG/TShader.h"

//using namespace irrklang;

int main(int argc, char *argv[])
{
    /*TDisplay display(800, 600,"Motor grafico");

    TMotorTAG  *motor   = new TMotorTAG();

    TNodo *nCamara = motor->crearCamara(glm::vec3(0, 0, 10), 45.0f, 800, 600, 0.1f, 1000.0f);
    TCamara *cCamara = dynamic_cast<TCamara*>(nCamara->getEntidad());


    int iCamara = motor->registrarCamara(nCamara);
    motor->setCamaraActiva(iCamara);

    TShader shader = motor->cargarShader("resources/res/basicShader");
    TNodo *nodoAnimacion = motor->cargarAnimacion("resources/res/animacion/mini_knight_fem_",20);

    while(!display.IsClosed())
    {
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

        shader.Bind();
        motor->draw();
        shader.Update(cCamara);

		display.Update();
    }*/

    Game* game = new Game();
    game->start_game();

}
