#include "Guardia.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"


void Guardia::inicializar_enemigo(Map* m)
{
    //De momento todos tienen el mismo body y cosas en comun asi que las inicializo para los tres en init
    init(m);
    EntityMgr->registrarEntity(this);
    EntityMgr->registrarGuardia(this);
    Structs::TColor color = {0,0,255,0};
    tipo = 1;
    modelo->cambiarColor(color);

}
void Guardia::investigar(){
     //mover medico con la lista de edges creada
    if(!listaEjes.empty() && it != listaEjes.end())
        toNextNodo = (*it).getDestination() - posicion;
    else
        toNextNodo=quietoParado;

    if(toNextNodo.Length() <= 1) //CUANDO LLEGA AL NODO
    {
        //moverBody(quietoParado);
        if(it != listaEjes.end()) //SI AUN NO ES EL ULTIMO NODO
            it++;
        else
            posicion = posicionInteres;
    }
    else
    { //CUANDO AUN NO HA LLEGADO A UN NODO
        //MoverEnemigo((*it).getDestination(),toNextNodo);
        toNextNodo.Normalize();
        posicion=posicion+toNextNodo*(avMovement*2);
        angulo = atan2f(((*it).getDestination().Z-posicion.Z) ,
                -((*it).getDestination().X-posicion.X)) * 180.f / irr::core::PI;
    }
    setPosition();

}
void Guardia::atacar(){
    Structs::TColor color = {0,255,0,0};
    modelo->cambiarColor(color);
    toProtaPosition = posicionProta - posicion;
    if(toProtaPosition.Length() > 5){
        toProtaPosition.Normalize();
        posicion = posicion + toProtaPosition*(avMovement*2.5);
        angulo = atan2f((posicionProta.Z-posicion.Z) ,
                -(posicionProta.X-posicion.X)) * 180.f / irr::core::PI;
    }
    else
        ataque();
    setPosition();
}
void Guardia::ataque(){
    EntityMgr->getEntityByID(0)->quitarVida();
    float mostrar = EntityMgr->getEntityByID(0)->getVida();
    std::cout<<"Vida player: "<<mostrar<<std::endl;
}
