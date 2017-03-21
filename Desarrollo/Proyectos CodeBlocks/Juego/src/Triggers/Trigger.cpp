#include "Trigger.h"
#include "TriggerRegion_Circle.h"
#include "TriggerRegion_Rectangle.h"

Trigger::Trigger()
{
    //ctor
}

Trigger::~Trigger()
{
    //dtor
    if (region) delete region;
}

bool Trigger::isTouchingTrigger(Structs::TPosicion EntityPos, double EntityRadius)const
{
    if (region){
        return region->isTouching(EntityPos, EntityRadius);
    }
    return false;
}

void Trigger::AddCircularRegion(Structs::TPosicion center, double radius)
{
  if (region)
    delete region;

  region = new TriggerRegion_Circle(center, radius);
}

void Trigger::AddRectangularRegion(Structs::TPosicion TopLeft, Structs::TPosicion BottomRight)
{
  if (region)
    delete region;

  region = new TriggerRegion_Rectangle(TopLeft, BottomRight);
}
