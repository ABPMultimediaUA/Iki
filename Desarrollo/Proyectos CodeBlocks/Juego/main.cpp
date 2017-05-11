
#include <SFML/Graphics.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::Texture texture;

    texture.loadFromFile("./resources/res/11.png");
    sf::Sprite sprite(texture);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear();


        // draw everything here...
        window.draw(sprite);

        // end the current frame
        window.display();
    }

    return 0;
}









/*#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "TDisplay.h"
#include "TMotorTAG.h"
#include "TShader.h"

#include "TDraw2D.h"

using namespace std;

int main()
{

    TDisplay window(1280, 720, "IKIGAI");

    TMotorTAG  *motor   = new TMotorTAG();

    TNodo *nCamara = motor->crearCamara(glm::vec3(0, 0, 10), 45.0f, 800, 600, 0.1f, 1000.0f);
    TCamara *cCamara = dynamic_cast<TCamara*>(nCamara->getEntidad());


    int iCamara = motor->registrarCamara(nCamara);
    motor->setCamaraActiva(iCamara);

    TDraw2D sprite("./resources/res/11.png");
    TNodo *nodoMalla = motor->crearMalla("./resources/res/cube2.obj");
    TShader shader = motor->cargarShader("./resources/res/basicShader");
    TNodo *nodoAnimacion = motor->cargarAnimacion("./resources/res/animacion/mini_knight_fem_",20);


    while (window.isOpen())
    {
        window.Clear(0.0f, 0.15f, 0.3f, 1.0f);

        window.Update();
        window.Draw(sprite.getSprite());
        shader.Bind();
        //motor->draw();
        shader.Update(cCamara);

        window.Display();
    }

}
/*
    Game* game = new Game();
    game->start_game();

}
*/
