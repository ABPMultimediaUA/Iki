#ifndef TRIGGER_MUNICION_H
#define TRIGGER_MUNICION_H

#include <Trigger_Respawning.h>
class GameEntity;

class Trigger_Municion : public Trigger_Respawning
{
    public:
        //this type of trigger is created when reading a map file
        Trigger_Municion(/*std::ifstream& datafile*/);
        virtual ~Trigger_Municion();

        //if triggered, this trigger will call the PickupWeapon method of the
        //bot. PickupWeapon will instantiate a weapon of the appropriate type.
        void Try(GameEntity*);
        //draws a symbol representing the weapon type at the trigger’s location
        void Render();

    protected:

    private:
};

#endif // TRIGGER_MUNICION_H
