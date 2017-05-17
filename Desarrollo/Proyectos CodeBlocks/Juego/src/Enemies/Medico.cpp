#include "Enemies/Medico.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"

Medico::~Medico(){
    delete aniMesh;
    body->GetWorld()->DestroyBody(body);
    delete modeloAtaque;
    ruta = nullptr;
    pRuta = nullptr;
    Mapa = nullptr;
    delete G_stateMachine;
    actualState = nullptr;
    oldState = nullptr;
    globalState = nullptr;
    grafo = nullptr;
    path = nullptr;
    delete memory;
    protegido = nullptr;
}

void Medico::inicializar_enemigo(Map* m)
{
    //De momento todos tienen el mismo body y cosas en comun asi que las inicializo para los tres en init
    init(m);
    tipo = 2;
    vida = 2;
    Structs::TColor color = {255,160,160,160};
    aniMesh = new AnimatedMesh("resources/Modelos/Medica.obj", color, posicion, 0);
    aniMesh->setTexture("resources/Texturas/medico.png");
    aniMesh->setScale(3);

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
        mirandoHacia=toNextNodo;
        toNextNodo.Normalize();
        posicion=posicion+toNextNodo*(avMovement*2.5);
        calcularAngulo((*it).getDestination());
    }
    setPosition();
}
void Medico::proteger(){

    toProtegido = protegido->getPosition() - posicion;
    if(toProtegido.Length()> 5){
        //MoverEnemigo(protegido->getPosition(),toProtegido);
        mirandoHacia=toProtegido;
        toProtegido.Normalize();
        posicion=posicion+toProtegido*(avMovement*2.5);
        calcularAngulo(protegido->getPosition());
    }
    else if (protegido->getVida()<4 && tiempoEnEstado>2){
        curar();
        resetTime();
    }
    //else
        //moverBody(quietoParado);
    setPosition();
}
void Medico::huir(){
    andarPath(2,posHuida);
    setPosition();
}
void Medico::curar(){
    if(protegido->getVida()>4)
        protegido->sumarVida();
}
