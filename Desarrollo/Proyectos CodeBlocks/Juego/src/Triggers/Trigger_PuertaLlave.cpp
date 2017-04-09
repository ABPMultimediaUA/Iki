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
            SoundMgr->cargarSonido("Triggers/tarjeta");
            SoundMgr->playSonido("Triggers/puerta_abrir");
        }else{
            static_cast<Player*>(ent)->NecesitoLlave();
        }
    }
    else{
        //aniMesh->setVisible(true);
        //body->SetActive(true);
    }
}

void Trigger_PuertaLlave::Update()
{

}
