#ifndef TRIGGER_PUERTA_H
#define TRIGGER_PUERTA_H

#include <Trigger.h>


class Trigger_Puerta : public Trigger
{
    public:
        Trigger_Puerta(float x, float z, float r);
        virtual ~Trigger_Puerta();

        void Try(GameEntity*);
        void Update();

        void triggerDisparado();
        void triggerFuera();
        bool isPuerta(){return true;}

    protected:

    private:

        bool fired = false;
        bool abierta = false;
        float mx,mz,ma;
};

#endif // TRIGGER_PUERTA_H
