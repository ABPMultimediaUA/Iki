#include "Guardia.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"

void Guardia::update(){
    G_stateMachine->Update();
    avMovement = 9.5*PhisicsWorld::getInstance()->getDeltaTime()/1000;
    tiempoEnEstado = PhisicsWorld::getInstance()->getDeltaTime()/1000 + tiempoEnEstado;
    std::cout<<"Tiempo en estado: "<< tiempoEnEstado<<std::endl;
}

void Guardia::inicializar_enemigo(Map* m)
{
    //De momento todos tienen el mismo body y cosas en comun asi que las inicializo para los tres en init
    init(m);
    registrarEnemigo(this);
    Structs::TColor color = {0,0,255,0};
    tipo = 1;
    direccion = 0;
    modelo->cambiarColor(color);

}
