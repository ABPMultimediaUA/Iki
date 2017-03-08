#ifndef TRIGGERFACTORY_H
#define TRIGGERFACTORY_H

#include "Trigger.h"

class TriggerFactory
{
    public:
        TriggerFactory();
        virtual ~TriggerFactory();

        Trigger *crearTrigger(int tipo, float z, float x, float r);

    protected:

    private:
};

#endif // TRIGGERFACTORY_H
