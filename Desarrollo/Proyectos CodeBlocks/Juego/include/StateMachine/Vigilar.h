#ifndef VIGILAR_H
#define VIGILAR_H

#include "StateMachine/State.h"

class Enemy;

class Vigilar : public State<Enemy>
{
    public:
        //es SINGLETON
        static Vigilar* Instance();
        void Enter(Enemy* enemigo);
        void Execute(Enemy* enemigo);
        void Exit(Enemy* enemigo);
        bool OnMessage(Enemy*, const Mensaje&);

    protected:

    private:
        Vigilar(){};
        Vigilar(const Vigilar&);
        Vigilar& operator=(const Vigilar&);
};

#endif // VIGILAR_H
