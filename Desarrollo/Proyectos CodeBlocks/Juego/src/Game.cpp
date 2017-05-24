#include "Game.h"
#include "Scene.h"
#include "Menu.h"
#include "../lib/irrKlang/conio.h"

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
    if(menu->run(0)){
        escena->inicializar_escena(1);
        escena = new Scene();
        escena->inicializar_escena(2);
    }
}
