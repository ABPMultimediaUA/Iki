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

bool TriggerRegion_Rectangle::isTouching(Structs::TPosicion EntityPos, double EntityRadius) const
{
    //distances calculated in squared-distance space
    if (  (BottomRight.Z > EntityPos.Z-EntityRadius && TopLeft.Z < EntityPos.Z-EntityRadius)
       // || TopLeft.Z     < EntityPos.Z+EntityRadius
       // || TopLeft.X     > EntityPos.X-EntityRadius
       /* || BottomRight.X < EntityPos.X+EntityRadius*/){

        return true;
    }

    return false;
}
