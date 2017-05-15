#include "Game.h"

#include <iostream>
#include "TDisplay.h"
#include "TDraw2D.h"
#include "TMotorTAG.h"
#include "TShader.h"




using namespace std;

int main()
{
    // create the window
    //TDisplay window(1360, 768, "IKIGAI");


    TMotorTAG  *motor   = new TMotorTAG();

    TNodo *nCamara = motor->crearCamara(glm::vec3(0, 0, 10), 45.0f, 800, 600, 0.1f, 1000.0f);
    TCamara *cCamara = dynamic_cast<TCamara*>(nCamara->getEntidad());


    int iCamara = motor->registrarCamara(nCamara);
    motor->setCamaraActiva(iCamara);

    sf::Vector2i tam(200, 200);
    TDraw2D hud("./resources/res/tuerca.png", tam);

    TNodo *nodoMalla = motor->crearMalla("./resources/res/cube2.obj");
    //TShader shader = motor->cargarShader("./resources/res/basicShader");
    TNodo *nodoAnimacion = motor->cargarAnimacion("./resources/res/animacion/mini_knight_fem_",20);

    hud.setPosition(20, 20);
    window.Draw2(); //m_window.pushGLStates();
    window.Draw(hud.getSprite());

    // run the program as long as the window is open
    while (window.isOpen())
    {
        window.Draw3(); ///m_window.popGLStates();

        window.Clear(0.0f, 0.15f, 0.3f, 1.0f);
        window.Update();

        shader.Bind();

        motor->draw();
        shader.Update(cCamara);

        window.Draw2(); ///m_window.pushGLStates();

        window.Draw(hud.getSprite());

        //window.Draw3(); //m_window.popGLStates();

        window.Display();
    }

    return 0;
}

/*
    Game* game = new Game();
    game->start_game();

}
*/
