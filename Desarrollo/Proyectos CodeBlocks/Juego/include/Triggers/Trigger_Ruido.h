#ifndef TRIGGER_RUIDO_H
#define TRIGGER_RUIDO_H

#include <Trigger.h>

class Trigger_Ruido : public Trigger
{
    public:
        Trigger_Ruido();
        virtual ~Trigger_Ruido();

        void Try(GameEntity*);
        void Update();

    private:
        speed = 0;
};

#endif // TRIGGER_RUIDO_H
