#ifndef TRIGGER_PUERTA_H
#define TRIGGER_PUERTA_H

#include <Trigger.h>


class Trigger_Puerta : public Trigger
{
    public:
        Trigger_Puerta();
        virtual ~Trigger_Puerta();

        //if triggered, this trigger will call the PickupWeapon method of the
        //bot. PickupWeapon will instantiate a weapon of the appropriate type.
        void Try(GameEntity*);
        //draws a symbol representing the weapon type at the trigger’s location
        void Update();
        void Render();

    protected:

    private:
};

#endif // TRIGGER_PUERTA_H
