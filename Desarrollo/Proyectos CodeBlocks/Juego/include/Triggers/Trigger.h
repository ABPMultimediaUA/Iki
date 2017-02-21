#ifndef TRIGGER_H
#define TRIGGER_H

#include <GameEntity.h>
#include "TriggerRegion.h"

class Trigger : public GameEntity
{
    public:
        Trigger();
        virtual ~Trigger();

//when this is called the trigger determines if the entity is within the
//trigger's region of influence. If it is then the trigger will be
//triggered and the appropriate action will be taken.
        ///virtual void Try(entity_type*) = 0;
//called each update step of the game. This method updates any internal
//state the trigger may have
        ///virtual void Update() = 0;

        bool isToBeRemoved()const{return m_bRemoveFromGame;}
        bool isActive(){return m_bActive;}

    protected:
        void SetToBeRemovedFromGame(){m_bRemoveFromGame = true;}
        void SetInactive(){m_bActive = false;}
        void SetActive(){m_bActive = true;}
//returns true if the entity given by a position and bounding radius is
//overlapping the trigger region
        bool isTouchingTrigger(Structs::TPosicion EntityPos, double EntityRadius)const;
//child classes use one of these methods to add a trigger region
        void AddCircularTriggerRegion(Structs::TPosicion center, double radius);
        void AddRectangularTriggerRegion(Structs::TPosicion TopLeft, Structs::TPosicion BottomRight);

    private:
//Every trigger owns a trigger region. If an entity comes within this
//region the trigger is activated
        TriggerRegion* m_pRegionOfInfluence;
//if this is true the trigger will be removed from the game on the
//next update
        bool m_bRemoveFromGame;
//it's convenient to be able to deactivate certain types of triggers
//on an event. Therefore a trigger can only be triggered when this
//value is true (respawning triggers make good use of this)
        bool m_bActive;
};

#endif // TRIGGER_H
