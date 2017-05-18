#ifndef TRIGGER_PUERTALLAVE_H
#define TRIGGER_PUERTALLAVE_H

#include <Trigger.h>


class Trigger_PuertaLlave : public Trigger
{
    public:
        Trigger_PuertaLlave(float x, float z, float r);
        virtual ~Trigger_PuertaLlave();

        void Try(GameEntity*);
        void Update();
        bool isPuerta(){return true;}
        bool isPuertaAbierta();

    protected:

    private:
        bool fired = false;
        bool abierta= false;
        float mx,mz,ma;
};

#endif // TRIGGER_PUERTALLAVE_H
