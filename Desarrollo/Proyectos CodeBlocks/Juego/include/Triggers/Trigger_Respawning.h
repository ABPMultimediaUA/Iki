#ifndef TRIGGER_RESPAWNING_H
#define TRIGGER_RESPAWNING_H

#include <Trigger.h>
class GameEntity;

class Trigger_Respawning : public Trigger
{
    public:
        Trigger_Respawning();
        virtual ~Trigger_Respawning();

        //to be implemented by child classes
        virtual void Try(GameEntity*) = 0;

    protected:
        //When a bot comes within this trigger's area of influence it is triggered
        //but then becomes inactive for a specified amount of time. These values
        //control the amount of time required to pass before the trigger becomes
        //active once more.
        int m_iNumUpdatesBetweenRespawns;
        int m_iNumUpdatesRemainingUntilRespawn;
        //sets the trigger to be inactive for m_iNumUpdatesBetweenRespawns
        //update steps
        void Deactivate()
        {
            SetInactive();
            m_iNumUpdatesRemainingUntilRespawn = m_iNumUpdatesBetweenRespawns;
        }
};

#endif // TRIGGER_RESPAWNING_H
