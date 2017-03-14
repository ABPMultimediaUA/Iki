#include "Medico.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"

void Medico::update(){
    G_stateMachine->Update();
    deltaTime = PhisicsWorld::getInstance()->getDeltaTime()/1000;
    avMovement = deltaTime * 9.5; //9.5 es la velocidad
    tiempoEnEstado = PhisicsWorld::getInstance()->getDeltaTime()/1000 + tiempoEnEstado;
}

void Medico::inicializar_enemigo(Map* m)
{
    //De momento todos tienen el mismo body y cosas en comun asi que las inicializo para los tres en init
    init(m);
    registrarEnemigo(this);
    Structs::TColor color = {0,0,0,255};
    tipo = 2;
    modelo->cambiarColor(color);
}
