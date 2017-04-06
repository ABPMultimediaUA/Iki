#include "Trigger_Puerta.h"
#include "GameEntity.h"
#include "SoundManager.h"

Trigger_Puerta::Trigger_Puerta()
{

}

Trigger_Puerta::~Trigger_Puerta()
{
    //dtor
}

void Trigger_Puerta::triggerDisparado()
{
    aniMesh->setVisible(false);
    body->SetActive(false);
    if (!fired){
        //if (!(SoundManager::getInstance()->isPlaying("alarma_sintetizada2"))){
        SoundMgr->soundStop("Triggers/puerta_cerrar");
        SoundMgr->playSonido("Triggers/puerta_abrir");
        fired = true;
    }
}

void Trigger_Puerta::triggerFuera()
{
    if (fired){
        SoundMgr->soundStop("Triggers/puerta_abrir");
        SoundMgr->playSonido("Triggers/puerta_cerrar");
    }
    fired = false;
    aniMesh->setVisible(true);
    body->SetActive(true);
}

void Trigger_Puerta::Try(GameEntity* ent)
{
    if (ent->isPlayer())
        if (isActive() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
            triggerDisparado();
        }else{
            triggerFuera();
        }
}

void Trigger_Puerta::Update()
{

}
