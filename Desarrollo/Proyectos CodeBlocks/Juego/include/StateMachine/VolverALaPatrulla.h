#ifndef VOLVERPATRULLA_H
#define VOLVERPATRULLA_H

#include "Enemies/StateMachine/State.h"

class Enemy;

class VolverALaPatrulla : public State<Enemy>
{
    public:
        //es SINGLETON
        static VolverALaPatrulla* Instance();
        void Enter(Enemy* enemigo);
        void Execute(Enemy* enemigo);
        void Exit(Enemy* enemigo);
        bool OnMessage(Enemy*, const Mensaje&);

    protected:

    private:
        VolverALaPatrulla(){};
        VolverALaPatrulla(const VolverALaPatrulla&);
        VolverALaPatrulla& operator=(const VolverALaPatrulla&);
};

#endif // VOLVERPATRULLA_H
