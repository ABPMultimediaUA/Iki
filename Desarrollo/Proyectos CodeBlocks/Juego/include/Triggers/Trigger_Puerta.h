#ifndef TRIGGER_PUERTA_H
#define TRIGGER_PUERTA_H

#include <Trigger.h>


class Trigger_Puerta : public Trigger
{
    public:
        Trigger_Puerta();
        virtual ~Trigger_Puerta();

        void Try(GameEntity*);
        void Update();

        void triggerDisparado();
        void triggerFuera();

    protected:

    private:

        bool fired = false;
};

#endif // TRIGGER_PUERTA_H
