#include "Trigger.h"
#include "TriggerRegion_Circle.h"
#include "TriggerRegion_Rectangle.h"

#include "Fachada/GraphicsFacade.h"

Trigger::Trigger()
{
    //ctor
}

Trigger::~Trigger()
{
    //dtor
    //if (region) delete region;
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
  if (region) delete region;

  region = new TriggerRegion_Circle(center, radius);
}
/*
void Trigger::AddRectangularRegion(Structs::TPosicion TopLeft, Structs::TPosicion BottomRight)
{
  if (region) delete region;

  region = new TriggerRegion_Rectangle(TopLeft, BottomRight);
}
*/
void Trigger::MoveRegion(Structs::TPosicion center)
{
  if (region)
        region->moveCenter(center);
}

void Trigger::Rotate()
{
    f32 tiempo = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
    if (tiempo - timer > 0.05){
        timer = tiempo;
        angulo += 2.5;
    }
    aniMesh->setRotation(angulo);
}

bool Trigger::noHayNingunaEntidad()
{
    int e = 0;
    std::vector<GameEntity*> ents = EntityMgr->getEntities();
    for(size_t i = 0; i < ents.size(); i++){
        if(isTouchingTrigger(ents[i]->getPosition(), ents[i]->getRadio()))
            e += 1;
        }
    if (e == 0){
       return true;
    }
    return false;
}
