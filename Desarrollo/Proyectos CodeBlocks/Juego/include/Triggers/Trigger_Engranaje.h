#ifndef TRIGGER_ENGRANAJE_H
#define TRIGGER_ENGRANAJE_H

#include <Trigger_Respawning.h>


class Trigger_Engranaje : public Trigger_Respawning
{
    public:
        Trigger_Engranaje();
        virtual ~Trigger_Engranaje();

        void Try(GameEntity*);
        void Update();

    protected:

    private:
};

#endif // TRIGGER_ENGRANAJE_H
