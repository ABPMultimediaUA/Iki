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

        void AddCircularRegion(Structs::TPosicion center, double radius);
        void AddRectangularRegion(Structs::TPosicion TopLeft, Structs::TPosicion BottomRight);

        bool isToBeRemoved()const{return removeFromGame;}
        bool isActive(){return active;}

    //protected:
        void SetToBeRemoved(){removeFromGame = true;}
        void SetInactive(){active = false;}
        void SetActive(){active = true;}

        bool isTouchingTrigger(Structs::TPosicion EntityPos, double EntityRadius)const;

    private:
        TriggerRegion* region = nullptr;
        bool removeFromGame;
        bool active;
};

#endif // TRIGGER_H
