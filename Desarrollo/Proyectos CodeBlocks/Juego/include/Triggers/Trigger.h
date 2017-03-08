#ifndef TRIGGER_H
#define TRIGGER_H

#include <GameEntity.h>
#include "TriggerRegion.h"

class Trigger : public GameEntity
{
    public:
        Trigger();
        virtual ~Trigger();

        virtual void Try(GameEntity*) = 0;
        virtual void Update() = 0;

        void AddCircularTriggerRegion(Structs::TPosicion center, double radius);
        void AddRectangularTriggerRegion(Structs::TPosicion TopLeft, Structs::TPosicion BottomRight);

        bool isToBeRemoved()const{return m_bRemoveFromGame;}
        bool isActive(){return m_bActive;}

    protected:
        void SetToBeRemoved(){m_bRemoveFromGame = true;}
        void SetInactive(){m_bActive = false;}
        void SetActive(){m_bActive = true;}

        bool isTouchingTrigger(Structs::TPosicion EntityPos, double EntityRadius)const;

    private:
        TriggerRegion* m_pRegionOfInfluence;
        bool m_bRemoveFromGame;
        bool m_bActive;
};

#endif // TRIGGER_H
