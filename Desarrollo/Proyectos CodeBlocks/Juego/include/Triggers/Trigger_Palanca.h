#ifndef TRIGGER_PALANCA_H
#define TRIGGER_PALANCA_H

#include "Trigger.h"

class Trigger_Apisonadora;

class Trigger_Palanca : public Trigger
{
    public:
        Trigger_Palanca();
        virtual ~Trigger_Palanca();

        void Try(GameEntity*);
        void Update(){};

    protected:

    private:
        Trigger_Apisonadora* apisonadora;
        bool kiko;
};

#endif // TRIGGER_PALANCA_H
