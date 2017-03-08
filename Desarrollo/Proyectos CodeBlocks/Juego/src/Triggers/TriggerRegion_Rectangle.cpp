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
    Structs s;
    if (   s.distance(TopLeft,     EntityPos) <= EntityRadius
        || s.distance(TopRight,    EntityPos) <= EntityRadius
        || s.distance(BottomLeft,  EntityPos) <= EntityRadius
        || s.distance(BottomRight, EntityPos) <= EntityRadius )
    {
       return true;
    }
    return false;
}
