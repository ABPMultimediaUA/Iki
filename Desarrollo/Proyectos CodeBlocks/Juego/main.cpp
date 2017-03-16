
#ifdef _MSC_VER

#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrKlang.h>
#include "driverChoice.h"
#include "lib/irrKlang/conio.h"
#include "Game.h"

using namespace irrklang;

int main()
{

    //INICIALIZAR ESCENA

#include <iostream>

std::cout << "==================" << std::endl;
std::cout << "     IKI GAME     " << std::endl;
std::cout << "==================" << std::endl;

/*
std::cout << "" << std::endl;
std::cout << "  _____ _  _______    _____          __  __ ______ " << std::endl;
std::cout << " |_   _| |/ /_   _|  / ____|   /\   |  \/  |  ____|" << std::endl;
std::cout << "   | | | ' /  | |   | |  __   /  \  | \  / | |__   " << std::endl;
std::cout << "   | | |  <   | |   | | |_ | / /\ \ | |\/| |  __|  " << std::endl;
std::cout << "  _| |_| . \ _| |_  | |__| |/ ____ \| |  | | |____ " << std::endl;
std::cout << " |_____|_|\_\_____|  \_____/_/    \_\_|  |_|______|" << std::endl;
std::cout << "" << std::endl;

*/

    Game* game = new Game();
    game->start_game();/*

    while(device->run())
    {
        vector3df cameraPos = escena.camera->getPosition();
        vector3df cameraTar = escena.camera->getTarget();

        if(receiver.isKeyDown(KEY_ESCAPE))
        {
            device->closeDevice();
            return 0;
        }
        else if(receiver.isKeyDown(KEY_RIGHT))
        {
            cameraPos.X+=0.1;
            cameraTar.X+=0.1;
        }
        else if (receiver.isKeyDown(KEY_LEFT))
        {
            cameraPos.X-=0.1;
            cameraTar.X-=0.1;
        }
        else if(receiver.isKeyDown(KEY_UP))
        {
            cameraPos.Z+=0.1;
            cameraTar.Z+=0.1;
        }
        else if (receiver.isKeyDown(KEY_DOWN))
        {
            cameraPos.Z-=0.1;
            cameraTar.Z-=0.1;
        }

        escena.camera->setPosition(cameraPos);
        escena.camera->setTarget(cameraTar);

        driver->beginScene(true, true, video::SColor(255,113,113,133));
        escena.render(); // draw the 3d scene
        driver->endScene();
    }

    device->drop();

    return 0;*/
}

/*
**/
