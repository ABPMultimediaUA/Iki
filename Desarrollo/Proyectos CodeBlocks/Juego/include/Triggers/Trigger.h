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
        //void AddRectangularRegion(Structs::TPosicion TopLeft, Structs::TPosicion BottomRight);
        void MoveRegion(Structs::TPosicion center);

        bool isToBeRemoved()const{return removeFromGame;}
        bool isActive(){return active;}

        void Rotate();
        bool noHayNingunaEntidad();

        bool HandleMessage(const Mensaje& msg){return false;}
        bool isPathObstructured(Structs::TPosicion){};
        bool canWalkBetween(Structs::TPosicion ,Structs::TPosicion){};
        virtual bool isPuerta(){return false;}
        virtual bool isApisonadora(){return false;}
        bool isTrigger(){return true;}

    protected:
        void SetToBeRemoved(){removeFromGame = true;}
        void SetInactive(){active = false;}
        void SetActive(){active = true;}

        bool isTouchingTrigger(Structs::TPosicion EntityPos, double EntityRadius)const;

        bool animation = false;
        float angulo = 0;
        f32 timer = 0;

    private:
        TriggerRegion* region = nullptr;
        bool removeFromGame = false;
        bool active = true;
};

#endif // TRIGGER_H
