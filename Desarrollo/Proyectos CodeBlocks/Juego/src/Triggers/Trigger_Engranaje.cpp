#include "Trigger_Engranaje.h"
#include "Player.h"

Trigger_Engranaje::Trigger_Engranaje()
{
    //ctor
}

Trigger_Engranaje::~Trigger_Engranaje()
{
    //dtor
}

void Trigger_Engranaje::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio()))
        if (ent->getVida() < 5){
            static_cast<Player*>(ent)->CogerVida();
            Deactivate();
            aniMesh->setVisible(false);
            SoundMgr->playSonido("Triggers/engranaje");
        }
}

void Trigger_Engranaje::Update()
{
    Rotate();
}
