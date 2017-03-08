#ifndef TRIGGERREGION_RECTANGLE_H
#define TRIGGERREGION_RECTANGLE_H

#include <TriggerRegion.h>


class TriggerRegion_Rectangle : public TriggerRegion
{
    public:
        TriggerRegion_Rectangle(Structs::TPosicion tl, Structs::TPosicion br);
        virtual ~TriggerRegion_Rectangle();

        bool isTouching(Structs::TPosicion EntityPos, float EntityRadius) const;

    protected:

    private:
        Structs::TPosicion TopLeft;
        Structs::TPosicion TopRight;
        Structs::TPosicion BottomLeft;
        Structs::TPosicion BottomRight;
};

#endif // TRIGGERREGION_RECTANGLE_H
