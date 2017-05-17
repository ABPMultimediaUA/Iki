#include "Trigger_Llave.h"
#include "Player.h"

Trigger_Llave::Trigger_Llave()
{

}

Trigger_Llave::~Trigger_Llave()
{
    //dtor
}

void Trigger_Llave::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
        static_cast<Player*>(ent)->CogerLlave();
        Deactivate();
        aniMesh->setVisible(false);
        SoundMgr->playSonido("Triggers/tarjeta");
    }
}

void Trigger_Llave::Update()
{
    Rotate();
}
