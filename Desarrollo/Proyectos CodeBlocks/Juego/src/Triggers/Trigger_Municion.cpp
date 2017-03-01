#include "Trigger_Municion.h"
#include "GameEntity.h"

Trigger_Municion::Trigger_Municion()
{
    //ctor
}

Trigger_Municion::~Trigger_Municion()
{
    //dtor
}

void Trigger_Municion::Try(GameEntity* ent)
{
    /*if (isActive() && isTouchingTrigger(ent->Pos(), ent->BRadius())){
        ent->PickupWeapon( EntityType() );
        Deactivate();
    }*/
}
