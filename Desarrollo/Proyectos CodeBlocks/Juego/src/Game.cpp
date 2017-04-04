#include "Game.h"
#include "Scene.h"
#include "Menu.h"

Game::Game()
{
    escena = new Scene();
    menu   = new Menu();
}

Game::~Game()
{
    delete escena;
    delete menu;
}

void Game::start_game(){
    menu->inicializar_menu(0);
    if(menu->run()){
        escena->inicializar_escena();
    }
}
