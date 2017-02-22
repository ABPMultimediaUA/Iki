#ifndef TRIGGERREGION_RECTANGLE_H
#define TRIGGERREGION_RECTANGLE_H

#include <TriggerRegion.h>


class TriggerRegion_Rectangle : public TriggerRegion
{
    public:
        TriggerRegion_Rectangle(Structs::TPosicion tl, Structs::TPosicion br);
        virtual ~TriggerRegion_Rectangle();

        virtual bool isTouching(Structs::TPosicion EntityPos, double EntityRadius);

    protected:

    private:
        Structs::TPosicion TopLeft;
        Structs::TPosicion BottomRight;
};

#endif // TRIGGERREGION_RECTANGLE_H
