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
    //delete m_pRegionOfInfluence;
}

bool Trigger::isTouchingTrigger(Structs::TPosicion EntityPos, double EntityRadius)const
{
    if (m_pRegionOfInfluence){
        return m_pRegionOfInfluence->isTouching(EntityPos, EntityRadius);
    }
    return false;
}

void Trigger::AddCircularTriggerRegion(Structs::TPosicion center, double radius)
{
  //if this replaces an existing region, tidy up memory
  //if (m_pRegionOfInfluence) delete m_pRegionOfInfluence;

  m_pRegionOfInfluence = new TriggerRegion_Circle(center, radius);
}

void Trigger::AddRectangularTriggerRegion(Structs::TPosicion TopLeft, Structs::TPosicion BottomRight)
{
  //if this replaces an existing region, tidy up memory
  //if (m_pRegionOfInfluence) delete m_pRegionOfInfluence;

  m_pRegionOfInfluence = new TriggerRegion_Rectangle(TopLeft, BottomRight);
}
