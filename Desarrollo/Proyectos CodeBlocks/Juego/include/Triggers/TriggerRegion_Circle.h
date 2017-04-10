#ifndef TRIGGERREGION_CIRCLE_H
#define TRIGGERREGION_CIRCLE_H

#include <TriggerRegion.h>


class TriggerRegion_Circle : public TriggerRegion
{
    public:
        TriggerRegion_Circle(Structs::TPosicion pos, float rad);
        virtual ~TriggerRegion_Circle();

        bool isTouching(Structs::TPosicion EntityPos, float EntityRadius) const;
        void moveCenter(Structs::TPosicion pos);

    protected:

    private:
        Structs::TPosicion center;
        float radius;
};

#endif // TRIGGERREGION_CIRCLE_H
