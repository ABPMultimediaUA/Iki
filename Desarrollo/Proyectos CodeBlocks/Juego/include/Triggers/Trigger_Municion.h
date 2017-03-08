#ifndef TRIGGER_MUNICION_H
#define TRIGGER_MUNICION_H

#include <Trigger_Respawning.h>
class GameEntity;

class Trigger_Municion : public Trigger_Respawning
{
    public:
        Trigger_Municion();
        virtual ~Trigger_Municion();
        void Try(GameEntity*);

        void Render();

    protected:

    private:
};

#endif // TRIGGER_MUNICION_H
