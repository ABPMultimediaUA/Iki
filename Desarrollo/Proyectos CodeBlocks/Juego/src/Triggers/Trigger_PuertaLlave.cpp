#include "Trigger_PuertaLlave.h"
#include "Player.h"

Trigger_PuertaLlave::Trigger_PuertaLlave()
{

}

Trigger_PuertaLlave::~Trigger_PuertaLlave()
{
    //dtor
}

void Trigger_PuertaLlave::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){

        if (static_cast<Player*>(ent)->GetLlaves() > 0){
            static_cast<Player*>(ent)->UsarLlave();
            aniMesh->setVisible(false);
            body->SetActive(false);
            SoundMgr->playSonido("Triggers/puerta_abrir");
            SoundMgr->playSonido("Triggers/acceso_confirmado");
            this->SetInactive();
        }else{
            if (!fired){
                SoundMgr->playSonido("Triggers/acceso_denegado");
                static_cast<Player*>(ent)->NecesitoLlave();
                fired = true;
            }
        }
    }

    if (ent->isPlayer() && !isTouchingTrigger(ent->getPosition(), ent->getRadio())){
        fired = false;
        //aniMesh->setVisible(true);
        //body->SetActive(true);
    }
}

void Trigger_PuertaLlave::Update()
{

}
