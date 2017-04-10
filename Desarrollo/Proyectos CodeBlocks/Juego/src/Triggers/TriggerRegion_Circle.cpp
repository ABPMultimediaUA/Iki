#include "TriggerRegion_Circle.h"

TriggerRegion_Circle::TriggerRegion_Circle(Structs::TPosicion pos, float rad)
{
    center = pos;
    radius = rad;
}

TriggerRegion_Circle::~TriggerRegion_Circle()
{
    //dtor
}

bool TriggerRegion_Circle::isTouching(Structs::TPosicion EntityPos, float EntityRadius) const
{
    if ( center.Distance(EntityPos) <= radius + EntityRadius )
    {
        return true;
    }
    return false;
}

void TriggerRegion_Circle::moveCenter(Structs::TPosicion pos)
{
    center = pos;
}
