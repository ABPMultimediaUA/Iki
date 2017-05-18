#include "Trigger_Palanca.h"
#include "Player.h"
#include "TriggerSystem.h"
#include "Trigger_Apisonadora.h"

Trigger_Palanca::Trigger_Palanca()
{
    std::vector<Trigger*> recorrer = TriggerSystem::getInstance()->GetTriggers();
    for(size_t i = 0; i < recorrer.size(); i++){
        if(recorrer[i]->isApisonadora())
            apisonadora = static_cast<Trigger_Apisonadora*>(recorrer[i]);
    }
    kiko = false;
}

Trigger_Palanca::~Trigger_Palanca()
{
    //dtor
}

void Trigger_Palanca::Try(GameEntity* ent)
{
    if (ent->isPlayer())
        if (isActive() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
            kiko = true;
            if(static_cast<Player*>(ent)->mostrarMensajePalanca()){
                apisonadora->ActDesact();
                /*if(apisonadora->isActive()){
                    apisonadora->setPosicionPlancha();
                    apisonadora->SetInactive();
                }
                else{
                    apisonadora->SetActive();
                }*/
            }
        }
        else
            if(kiko){
                static_cast<Player*>(ent)->desmostrarMensajePalanca();
                kiko = false;
            }
}
