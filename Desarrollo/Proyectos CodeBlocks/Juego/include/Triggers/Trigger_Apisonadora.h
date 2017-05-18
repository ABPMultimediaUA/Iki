#ifndef TRIGGER_APISONADORA_H
#define TRIGGER_APISONADORA_H

#include <Trigger.h>

class Trigger_Apisonadora : public Trigger
{
    public:
        Trigger_Apisonadora(float x, float z, float r);
        virtual ~Trigger_Apisonadora();

        void Try(GameEntity*);
        void Update();

        void movimiento_apisonadora();
        void setPosicionPlancha();

        bool isApisonadora(){ return true;}
        void ActDesact();

    protected:

    private:
        MeshSceneNode* plancha;
        bool bajando;
};

#endif // TRIGGER_APISONADORA_H
