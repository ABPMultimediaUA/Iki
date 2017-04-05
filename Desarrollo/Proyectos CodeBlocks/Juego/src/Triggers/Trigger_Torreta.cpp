#include "Trigger_Torreta.h"

Trigger_Torreta::Trigger_Torreta()
{
    //ctor
}

Trigger_Torreta::~Trigger_Torreta()
{
    //dtor
}

void Trigger_Torreta::calcularAngulo(Structs::TPosicion p1){
    angulo = atan2f((p1.Z-posicion.Z) ,
                -(p1.X-posicion.X)) * 180.f / irr::core::PI;
}

void Trigger_Torreta::triggerDisparado()
{
    fired = true;
    if(GraphicsFacade::getInstance().getTimer()->getTime/1000.f - time_fired > 2){

    }

}

void Trigger_Torreta::Try(GameEntity* ent)
{
    if (ent->isPlayer())
        if (isActive() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
            if(true) //Aqui va el calculo del angulo
                calcularAngulo(ent.getPosition());
            if(!fired){
                time_fired = GraphicsFacade::getInstance().getTimer()->getTime/1000.f;
                triggerDisparado();
            }
        }else{
            fired = false;
        }

}

void Trigger_Torreta::Update()
{
    setPosition();
    if (fired && GraphicsFacade::getInstance().getTimer()->getTime/1000.f - time_fired > 2){
        disparo();
    }
}

void Trigger_Puerta::disparo(){
    input.p1.Set(enemigos[5]->getBody()->GetPosition().x, enemigos[5]->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo
            input.p2.Set(prota->getBody()->GetPosition().x, prota->getBody()->GetPosition().y);	//	Punto	final	del	rayo

    distancia = sqrt(pow(input.p2.x-input.p1.x, 2)+pow(input.p2.y-input.p1.y, 2));
}
