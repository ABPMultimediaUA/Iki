#ifndef TRIGGERREGION_CIRCLE_H
#define TRIGGERREGION_CIRCLE_H

#include <TriggerRegion.h>


class TriggerRegion_Circle : public TriggerRegion
{
    public:
        TriggerRegion_Circle(Structs::TPosicion pos, double rad);
        virtual ~TriggerRegion_Circle();

        bool isTouching(Structs::TPosicion EntityPos, double EntityRadius) const;

    protected:

    private:
        Structs::TPosicion center;
        double radius;
};

#endif // TRIGGERREGION_CIRCLE_H
