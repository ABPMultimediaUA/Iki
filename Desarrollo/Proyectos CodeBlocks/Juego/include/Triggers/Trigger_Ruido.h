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

        void activar(){ SetActive(); }
        void desactivar(){ SetInactive(); }

    private:
        int speed = 0;
        Structs::TPosicion post;
};

#endif // TRIGGER_RUIDO_H
