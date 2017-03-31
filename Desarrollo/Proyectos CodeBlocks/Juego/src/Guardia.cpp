#include "Guardia.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"


void Guardia::inicializar_enemigo(Map* m)
{
    //De momento todos tienen el mismo body y cosas en comun asi que las inicializo para los tres en init
    init(m);
    tipo = 1;
    Structs::TColor color = {0,0,255,0};
    modelo->cambiarColor(color);

}
void Guardia::investigar(){
    andarPath(2,posicionInteres);
    setPosition();

}
void Guardia::atacar(){
    Structs::TColor color = {0,255,0,0};
    modelo->cambiarColor(color);
    toProtaPosition = posicionProta - posicion;
    if(toProtaPosition.Length() > 5){
        toProtaPosition.Normalize();
        posicion = posicion + toProtaPosition*(avMovement*2);
        calcularAngulo(posicionProta);
    }
    else
        ataque();
    setPosition();
}
void Guardia::ataque(){
    EntityMgr->getEntityByID(0)->quitarVida();
    float mostrar = EntityMgr->getEntityByID(0)->getVida();
    //std::cout<<"Vida player: "<<mostrar<<std::endl;
}
