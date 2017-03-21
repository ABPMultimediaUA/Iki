#include "Medico.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"


void Medico::inicializar_enemigo(Map* m)
{
    //De momento todos tienen el mismo body y cosas en comun asi que las inicializo para los tres en init
    init(m);
    EntityMgr->registrarEntity(this);
    Structs::TColor color = {0,0,0,255};
    tipo = 2;
    modelo->cambiarColor(color);
}
void Medico::pedirAyuda(){
    //mover medico con la lista de edges creada
    if(!listaEjes.empty() && it != listaEjes.end())
        toNextNodo = (*it).getDestination() - posicion;
    else
        toNextNodo=quietoParado;

    if(toNextNodo.Length() <= 1) //CUANDO LLEGA AL NODO
    {
        if(it != listaEjes.end()) //SI AUN NO ES EL ULTIMO NODO
            it++;
    }
    else
    { //CUANDO AUN NO HA LLEGADO A UN NODO
        toNextNodo.Normalize();
        posicion = posicion + toNextNodo * (avMovement*1.5);
    }

    angulo = atan2f((toNextNodo.Z-posicion.Z) ,-(toNextNodo.X-posicion.X)) * 180.f /PI;
    setPosition();
}
void Medico::proteger(){
    toProtegido = protegido->getPosition() - posicion;
    if(toProtegido.Length()>5){
        toProtegido.Normalize();
        posicion = posicion + toProtegido * (avMovement*1.5);
        angulo = atan2f((toProtegido.Z-posicion.Z) ,-(toProtegido.X-posicion.X)) * 180.f /PI;
        setPosition();
    }
}
