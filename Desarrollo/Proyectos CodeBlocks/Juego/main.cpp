#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "TDisplay.h"
#include "TMotorTAG.h"
#include "TShader.h"


using namespace std;

int main()
{
    TDisplay window(1920, 1080, "IKIGAI");

    TMotorTAG  *motor   = new TMotorTAG();

    TNodo *nCamara = motor->crearCamara(glm::vec3(0, 0, 10), 45.0f, 800, 600, 0.1f, 1000.0f);
    TCamara *cCamara = dynamic_cast<TCamara*>(nCamara->getEntidad());


    int iCamara = motor->registrarCamara(nCamara);
    motor->setCamaraActiva(iCamara);

    TNodo *nodoMalla = motor->crearMalla("./resources/res/cube2.obj");
    TShader shader = motor->cargarShader("./resources/res/basicShader");
    TNodo *nodoAnimacion = motor->cargarAnimacion("./resources/res/animacion/mini_knight_fem_",20);


    while (window.isOpen())
    {
        window.Clear(0.0f, 0.15f, 0.3f, 1.0f);

        window.Update();

        shader.Bind();
        motor->draw();
        shader.Update(cCamara);

        window.Display();
    }

}
/*
    Game* game = new Game();
    game->start_game();

}
*/
