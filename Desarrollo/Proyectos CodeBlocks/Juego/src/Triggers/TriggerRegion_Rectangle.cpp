#include "TriggerRegion_Rectangle.h"

TriggerRegion_Rectangle::TriggerRegion_Rectangle(Structs::TPosicion tl, Structs::TPosicion br)
{
    TopLeft = tl;
    TopRight = {TopLeft.X, 0, BottomRight.Z};
    BottomLeft = {BottomRight.X, 0, TopLeft.Z};
    BottomRight = br;
}

TriggerRegion_Rectangle::~TriggerRegion_Rectangle()
{
    //dtor
}

bool TriggerRegion_Rectangle::isTouching(Structs::TPosicion EntityPos, float EntityRadius) const
{
    /// BUG HERE, BAD CALCULATED
    if (   EntityPos.Distance(TopLeft)     <= EntityRadius
        || EntityPos.Distance(TopRight)    <= EntityRadius
        || EntityPos.Distance(BottomLeft)  <= EntityRadius
        || EntityPos.Distance(BottomRight) <= EntityRadius )
    {
       return true;
    }
    return false;
}
