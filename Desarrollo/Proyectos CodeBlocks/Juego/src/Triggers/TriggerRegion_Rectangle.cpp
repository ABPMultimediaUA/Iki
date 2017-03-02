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
    //if (  //  TopLeft.X     TopLeft.Z       distance   EntityPos.X EntityPos.Z
          //  TopLeft.X     BottomRight.Z   distance   EntityPos.X EntityPos.Z
          //  BottomRight.X TopLeft.Z       distance   EntityPos.X EntityPos.Z
          //  BottomRight.X BottomRight.Z   distance   EntityPos.X EntityPos.Z    {
    //    return true;
    //}

    return false;
}
