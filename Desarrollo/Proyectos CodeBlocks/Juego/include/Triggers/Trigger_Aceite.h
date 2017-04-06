#ifndef TRIGGER_ACEITE_H
#define TRIGGER_ACEITE_H


#include <Trigger_Respawning.h>
class GameEntity;

class Trigger_Aceite : public Trigger_Respawning
{
    public:
        Trigger_Aceite();
        virtual ~Trigger_Aceite();

        void Try(GameEntity*);
        void Update();

    protected:

    private:
};

#endif // TRIGGER_ACEITE_H
