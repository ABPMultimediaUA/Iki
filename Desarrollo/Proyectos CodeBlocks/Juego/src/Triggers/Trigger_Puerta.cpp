#include "Trigger_Puerta.h"
#include "GameEntity.h"
#include "EntityManager.h"
#include "SoundManager.h"

Trigger_Puerta::Trigger_Puerta()
{
    SoundManager::getInstance()->cargarSonido("puerta_abrir");
    SoundManager::getInstance()->cargarSonido("puerta_cerrar");
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
        SoundManager::getInstance()->soundStop("puerta_cerrar");
        SoundManager::getInstance()->playSonido("puerta_abrir");
        fired = true;
    }
}

void Trigger_Puerta::triggerFuera()
{
    if (fired){
        SoundManager::getInstance()->soundStop("puerta_abrir");
        SoundManager::getInstance()->playSonido("puerta_cerrar");
    }
    fired = false;
    aniMesh->setVisible(true);
    body->SetActive(true);
}

void Trigger_Puerta::Try(GameEntity* ent)
{
    //if (ent->isPlayer())
        if (isActive() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
            triggerDisparado();
        }
}

void Trigger_Puerta::Update()
{
    if(noHayNingunaEntidad())
        triggerFuera();
}

