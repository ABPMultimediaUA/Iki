#ifndef TRIGGER_LLAVE_H
#define TRIGGER_LLAVE_H

#include <Trigger_Respawning.h>


class Trigger_Llave : public Trigger_Respawning
{
    public:
        Trigger_Llave();
        virtual ~Trigger_Llave();

        void Try(GameEntity*);
        void Update();

    protected:

    private:
};

#endif // TRIGGER_LLAVE_H
