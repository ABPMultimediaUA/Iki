#include "TriggerRegion_Rectangle.h"

TriggerRegion_Rectangle::TriggerRegion_Rectangle(Structs::TPosicion tl, Structs::TPosicion br)
{
    TopLeft = tl;
    BottomRight = br;
}

TriggerRegion_Rectangle::~TriggerRegion_Rectangle()
{
    //dtor
}

bool TriggerRegion_Rectangle::isTouching(Structs::TPosicion EntityPos, double EntityRadius)
{
    //distances calculated in squared-distance space

    return false;
}
