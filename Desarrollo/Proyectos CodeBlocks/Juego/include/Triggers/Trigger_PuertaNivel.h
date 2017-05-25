#ifndef TRIGGER_PUERTANIVEL_H
#define TRIGGER_PUERTANIVEL_H

#include <Trigger.h>


class Trigger_PuertaNivel : public Trigger
{
    public:
        Trigger_PuertaNivel(float x, float z, float r);
        virtual ~Trigger_PuertaNivel();

        void Try(GameEntity*);
        void Update();

    protected:

    private:
        bool fired = false;
};

#endif // TRIGGER_PUERTANIVEL_H
