#ifndef TRIGGER_PUERTALLAVE_H
#define TRIGGER_PUERTALLAVE_H

#include <Trigger.h>


class Trigger_PuertaLlave : public Trigger
{
    public:
        Trigger_PuertaLlave();
        virtual ~Trigger_PuertaLlave();

        void Try(GameEntity*);
        void Update();

    protected:

    private:
};

#endif // TRIGGER_PUERTALLAVE_H
