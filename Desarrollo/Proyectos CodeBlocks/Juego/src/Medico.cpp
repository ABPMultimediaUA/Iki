#include "Medico.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"


void Medico::inicializar_enemigo(Map* m)
{
    //De momento todos tienen el mismo body y cosas en comun asi que las inicializo para los tres en init
    init(m);
    Structs::TColor color = {0,0,0,255};
    modelo->cambiarColor(color);
    tipo = 2;
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
        else if(posicion.Distance(getGuardiaMasCercano()->getPosition())>15)
            crearPath(getGuardiaMasCercano()->getPosition());
    }
    else
    { //CUANDO AUN NO HA LLEGADO A UN NODO
        //MoverEnemigo((*it).getDestination(),toNextNodo);
        toNextNodo.Normalize();
        mirandoHacia=toNextNodo;
        posicion=posicion+toNextNodo*(avMovement*2.5);
        calcularAngulo((*it).getDestination());
    }
    setPosition();
}
void Medico::proteger(){

    toProtegido = protegido->getPosition() - posicion;
    if(toProtegido.Length()> 5){
        //MoverEnemigo(protegido->getPosition(),toProtegido);
        toProtegido.Normalize();
        mirandoHacia=toProtegido;
        posicion=posicion+toProtegido*(avMovement*2.5);
        calcularAngulo(protegido->getPosition());
    }
    //else
        //moverBody(quietoParado);
    setPosition();
}
