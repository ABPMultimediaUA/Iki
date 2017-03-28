#include "Trigger_Puerta.h"
#include "GameEntity.h"
#include "SoundManager.h"

Trigger_Puerta::Trigger_Puerta()
{
    SoundManager::getInstance()->cargarSonido("alarma_sintetizada2");
    //SoundManager::getInstance()->volumenSonido(2.0f,"alarma_sintetizada2");
}

Trigger_Puerta::~Trigger_Puerta()
{
    //dtor
}

void Trigger_Puerta::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
       aniMesh->setVisible(false);
       body->SetActive(false);
       if (!(SoundManager::getInstance()->isPlaying("alarma_sintetizada2"))){
            std::cout << "fdsdf" << std::endl;
            SoundManager::getInstance()->playSonido("alarma_sintetizada2");
       }else{
            std::cout << "  " << std::endl;
       }
    }
    else{
        aniMesh->setVisible(true);
        body->SetActive(true);
    }
}

void Trigger_Puerta::Update()
{

}
