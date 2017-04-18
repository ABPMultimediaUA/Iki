#ifndef TRIGGER_TORRETA_H
#define TRIGGER_TORRETA_H

#include <Trigger.h>


class Trigger_Torreta : public Trigger
{
    public:
        Trigger_Torreta();
        virtual ~Trigger_Torreta();
        void calcularAngulo(Structs::TPosicion);
        void triggerDisparado();
        void Try(GameEntity*);
        void Update();
        void disparo();
    protected:

    private:
        float angulo;
        bool fired;
};

#endif // TRIGGER_TORRETA_H
