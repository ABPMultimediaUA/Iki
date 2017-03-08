#ifndef TRIGGERREGION_H
#define TRIGGERREGION_H

#include "Structs.h"

class TriggerRegion
{
    public:
        TriggerRegion();
        virtual ~TriggerRegion();

        virtual bool isTouching(Structs::TPosicion EntityPos, float EntityRadius)const = 0;

    protected:

    private:

};

#endif // TRIGGERREGION_H
