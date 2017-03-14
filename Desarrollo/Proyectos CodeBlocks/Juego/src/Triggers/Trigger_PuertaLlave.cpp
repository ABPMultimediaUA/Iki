#include "Trigger_PuertaLlave.h"
#include "Player.h"


Trigger_PuertaLlave::Trigger_PuertaLlave()
{
    //ctor
    SetActive();
}

Trigger_PuertaLlave::~Trigger_PuertaLlave()
{
    //dtor
}
#include <iostream>
void Trigger_PuertaLlave::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){

        if (static_cast<Player*>(ent)->GetLlaves() > 0){
            //Open la puerta
            //std::cout << " abierta " << std::endl;
            static_cast<Player*>(ent)->UsarLlave();
            aniMesh->setVisible(false);
            body->SetActive(false);
        }else{
            std::cout << " Necesitas una llave " << std::endl;
        }
    }
    else{
        //Close la puerta
        //std::cout << " cerrada " << std::endl;
        aniMesh->setVisible(true);
        body->SetActive(true);
    }
}

void Trigger_PuertaLlave::Update()
{

}

void Trigger_PuertaLlave::Render()
{

}
