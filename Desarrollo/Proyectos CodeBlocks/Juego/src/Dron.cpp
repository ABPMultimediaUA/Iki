#include "Dron.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"

void Dron::update(){
    G_stateMachine->Update();
    avMovement=9.5*PhisicsWorld::getInstance()->getDeltaTime()/1000;
    tiempoEnEstado = PhisicsWorld::getInstance()->getDeltaTime() + tiempoEnEstado;
}

void Dron::inicializar_enemigo(Map* m)
{
    //De momento todos tienen el mismo body y cosas en comun asi que las inicializo para los tres en init
    init(m);
    Structs::TColor color = {0,255,0,0};
    tipo = 3;
    direccion = 0;
    modelo->cambiarColor(color);
}
